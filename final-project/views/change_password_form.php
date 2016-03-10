<form action="change_password.php" method="post">
    <fieldset>
        <div class="form-group">
            <input class="form-control" name="old-password" placeholder="Old password" type="password"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="new-password" placeholder="New password" type="password"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="new-password-confirmation" placeholder="New password (again)" type="password"/>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                <span aria-hidden="true" class="glyphicon glyphicon-log-in"></span>
                Change Password
            </button>
        </div>
    </fieldset>
</form>