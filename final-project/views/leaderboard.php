<h3>Leaderboard</h3>
<h5><?= $user[0]['username'] ?>'s score: <?= $user[0]['score'] ?></h5>
<table class="table">
    <thead>
        <tr>
            <th>Username</th>
            <th>Score</th>
        </tr>
    </thead>
    <tbody>
        <?php foreach ($rankings as $ranking): ?>
            <tr>
                <td><?= $ranking["username"] ?></td>
                <td><?= $ranking["score"] ?></td>
            </tr>
        <?php endforeach ?>
    </tbody>
</table>