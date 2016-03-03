/* global google */
/* global _ */
/**
 * scripts.js
 *
 * Computer Science 50
 * Problem Set 8
 *
 * Global JavaScript.
 */

// Google Map
var map;

// markers for map
var markers = [];

// info window
var info = new google.maps.InfoWindow();

// execute when the DOM is fully loaded
$(function() {

    // styles for map
    // https://developers.google.com/maps/documentation/javascript/styling
    var styles = [

        // hide Google's labels
        {
            featureType: "all",
            elementType: "labels",
            stylers: [
                {visibility: "off"}
            ]
        },

        // hide roads
        {
            featureType: "road",
            elementType: "geometry",
            stylers: [
                {visibility: "off"}
            ]
        }

    ];

    // options for map
    // https://developers.google.com/maps/documentation/javascript/reference#MapOptions
    var options = {
        center: {lat: 42.3770, lng: -71.1256}, // Cambridge, MA
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        maxZoom: 11,
        panControl: true,
        styles: styles,
        zoom: 13,
        zoomControl: true
    };

    // get DOM node in which map will be instantiated
    var canvas = $("#map-canvas").get(0);

    // instantiate map
    map = new google.maps.Map(canvas, options);

    // configure UI once Google Map is idle (i.e., loaded)
    google.maps.event.addListenerOnce(map, "idle", configure);

    // "personal touch" spec requirement  (chose to use ground overlays)
    var image1Bounds = {
        north: 42.453733,
        south: 42.35,
        east: -70.7,
        west: -70.9
    };

    historicalOverlay = new google.maps.GroundOverlay(
        'https://www.mgraves.org/wp-content/uploads/2010/12/BIG-LOOK-HERE-ARROW-copy.png', image1Bounds);
    historicalOverlay.setMap(map);

    var image2Bounds = {
        north: 43.2,
        south: 42.1,
        east: -68.75,
        west: -70.55
    };

    historicalOverlay = new google.maps.GroundOverlay(
        'https://49.media.tumblr.com/a7d7323885509fa85478fd30af784af9/tumblr_n6sxu83sGe1scd4jmo1_400.gif', image2Bounds);
    historicalOverlay.setMap(map);
});

/**
 * Adds marker for place to map.
 */
function addMarker(place)
{
    // store place's latitute and longitude in a variable
    var myLatlng = new google.maps.LatLng(parseFloat(place.latitude), parseFloat(place.longitude));

    // create labeled marker
    var marker = new MarkerWithLabel({
        position: myLatlng,
        map: map,
        labelContent: place.place_name + ", " + place.admin_code1,
        labelAnchor: new google.maps.Point(50, 0),
        labelClass: "label",
        labelStyle: {opacity: 0.75}
    });

    // load articles in info window upon label click
    google.maps.event.addListener(marker, "click", function() { loadInfoWindow(place, marker) });

    // add marker to global markers array
    markers.push(marker);
}

/**
 * Configures application.
 */
function configure()
{
    // update UI after map has been dragged
    google.maps.event.addListener(map, "dragend", function() {
        update();
    });

    // update UI after zoom level changes
    google.maps.event.addListener(map, "zoom_changed", function() {
        update();
    });

    // remove markers whilst dragging
    google.maps.event.addListener(map, "dragstart", function() {
        removeMarkers();
    });

    // configure typeahead
    // https://github.com/twitter/typeahead.js/blob/master/doc/jquery_typeahead.md
    $("#q").typeahead({
        autoselect: true,
        highlight: true,
        minLength: 1
    },
    {
        source: search,
        templates: {
            empty: "no places found yet",
            suggestion: _.template("<p><%- place_name %>, <%- admin_name1 %> <span style='color: #C0C0C0;'><%- postal_code %></span></p>")
        }
    });

    // re-center map after place is selected from drop-down
    $("#q").on("typeahead:selected", function(eventObject, suggestion, name) {

        // ensure coordinates are numbers
        var latitude = (_.isNumber(suggestion.latitude)) ? suggestion.latitude : parseFloat(suggestion.latitude);
        var longitude = (_.isNumber(suggestion.longitude)) ? suggestion.longitude : parseFloat(suggestion.longitude);

        // set map's center
        map.setCenter({lat: latitude, lng: longitude});

        // update UI
        update();
    });

    // hide info window when text box has focus
    $("#q").focus(function(eventData) {
        hideInfo();
    });

    // re-enable ctrl- and right-clicking (and thus Inspect Element) on Google Map
    // https://chrome.google.com/webstore/detail/allow-right-click/hompjdfbfmmmgflfjdlnkohcplmboaeo?hl=en
    document.addEventListener("contextmenu", function(event) {
        event.returnValue = true; 
        event.stopPropagation && event.stopPropagation(); 
        event.cancelBubble && event.cancelBubble();
    }, true);

    // update UI
    update();

    // give focus to text box
    $("#q").focus();
}

/**
 * Hides info window.
 */
function hideInfo()
{
    info.close();
}

/**
 * Create info window html content.
 */
function htmlInfoWindow(data)
{
    // start unordered list
    var ul = "<ul>";

    // create template using Underscore library
    var template = _.template("<li><a href='<%- link %>' target='_blank'><%- title %></a></li>");

    // insert link and link title into template
    var len_data = data.length;
    for (var i = 0; i < len_data; i++)
    {
        ul += template({
            link: data[i].link,
            title: data[i].title
        }); 
    }

    // end unordered list
    ul += "</ul>";

    return ul;
}

/**
 * Load info window html content.
 */
function loadInfoWindow(place, marker)
{
    showInfo(marker);

    $.getJSON("articles.php", "geo=" + place.postal_code)
    .done(function(data, textStatus, jqXHR) 
    {
        // if no news in postal code area, call getJSON on place name instead
	if (data.length === 0)
	{
	    $.getJSON("articles.php", "geo=" + place.place_name)
            .done(function(data, textStatus, jqXHR) 
            {
                // if no news in place name area, fill info window with placeholder text
                if (data.length === 0)
        	{
        	    showInfo(marker, "No news for this area.");
        	}
        	// else if news exists in place name area, display news in info window
        	else
                {
                    // dynamically create list of articles in html
        	    ul = htmlInfoWindow(data);
        	    
        	    // show news
                    showInfo(marker, ul);
        	}
            });
	}
	// else if news exists in postal code area, displays news in info window
	else
	{
            // dynamically create list of articles in html
    	    ul = htmlInfoWindow(data);

            // show news
    	    showInfo(marker, ul);
        }
    });
}

/**
 * Removes markers from map.
 */
function removeMarkers()
{
    // iterate through global markers array
    var len_markers = markers.length;
    for (var i = 0; i < len_markers; i++)
    {
        // remove marker from map
        markers[i].setMap(null);
    }

    // empty array
    markers.length = 0;
}

/**
 * Searches database for typeahead's suggestions.
 */
function search(query, cb)
{
    // get places matching query (asynchronously)
    var parameters = {
        geo: query
    };
    $.getJSON("search.php", parameters)
    .done(function(data, textStatus, jqXHR) {

        // call typeahead's callback with search results (i.e., places)
        cb(data);
    })
    .fail(function(jqXHR, textStatus, errorThrown) {

        // log error to browser's console
        console.log(errorThrown.toString());
    });
}

/**
 * Shows info window at marker with content.
 */
function showInfo(marker, content)
{
    // start div
    var div = "<div id='info'>";
    if (typeof(content) === "undefined")
    {
        // http://www.ajaxload.info/
        div += "<img alt='loading' src='img/ajax-loader.gif'/>";
    }
    else
    {
        div += content;
    }

    // end div
    div += "</div>";

    // set info window's content
    info.setContent(div);

    // open info window (if not already open)
    info.open(map, marker);
}

/**
 * Updates UI's markers.
 */
function update() 
{
    // get map's bounds
    var bounds = map.getBounds();
    var ne = bounds.getNorthEast();
    var sw = bounds.getSouthWest();

    // get places within bounds (asynchronously)
    var parameters = {
        ne: ne.lat() + "," + ne.lng(),
        q: $("#q").val(),
        sw: sw.lat() + "," + sw.lng()
    };
    $.getJSON("update.php", parameters)
    .done(function(data, textStatus, jqXHR) {

        // remove old markers from map
        removeMarkers();

        // add new markers to map
        for (var i = 0; i < data.length; i++)
        {
            addMarker(data[i]);
        }
     })
     .fail(function(jqXHR, textStatus, errorThrown) {

         // log error to browser's console
         console.log(errorThrown.toString());
     });
}
