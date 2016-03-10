<h5><?= $user[0]['username'] ?>'s score: <?= $user[0]['score'] ?></h5>
<h3>Is this a Rick or a stick?</h3>
<img src="<?= $image[0]['url'] ?>" alt="Rick or Stick?" style="height: 42vh; padding-top: 12px; padding-bottom: 10px;">
<br><br>
<form action="answer.php" method="post">
  <button name="answer" class="btn btn-default" type="submit" value="<?= "rick" . "^" . $image[0]['type'] . "^" . $image[0]['url'] . "^" . $image[0]['name'] ?>">Rick</button>
  <button name="answer" class="btn btn-default" type="submit" value="<?= "stick" . "^" . $image[0]['type'] . "^" . $image[0]['url'] . "^" . $image[0]['name'] ?>">Stick</button>
</form>