<style>
    body
    {
        background-color: <?= $background ?>;
    }
</style>
<h5><?= $user[0]['username'] ?>'s score: <?= $user[0]['score'] ?></h5>
<h3><?= htmlspecialchars($message) ?></h3>
<img src="<?= $url ?>" alt="Rick or Stick?" style="height: 42vh; padding-top: 12px; padding-bottom: 10px;">
<br><br>
<a href="/"><button class="btn btn-default">Play again</button></a>