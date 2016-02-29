<h1><?= $user[0]["username"] ?>'s portfolio</h1>
<table class="table table-striped">
    <thead>
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price</th>
            <th>Total</th>
        </tr>
    </thead>
    <tbody>
        <?php foreach ($positions as $position): ?>
            <tr>
                <td><?= $position["symbol"] ?></td>
                <td><?= $position["name"] ?></td>
                <td><?= $position["shares"] ?></td>
                <td>$<?= $position["price"] ?></td>
                <td>$<?= $position["total"] ?></td>
            </tr>
        <?php endforeach ?>
        <tr>
            <td colspan="4">CASH</td>
            <td>$<?= $user[0]["cash"] ?></td>
        </tr>
    </tbody>
</table>