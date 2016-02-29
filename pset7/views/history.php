<table class="table table-striped">
    <thead>
        <tr>
            <th>Transaction</th>
            <th>Date/Time</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
    </thead>
    <tbody>
        <?php foreach ($transactions as $transaction): ?>
            <tr>
                <td><?= $transaction["transaction"] ?></td>
                <td><?= $transaction["datetime"] ?></td>
                <td><?= $transaction["symbol"] ?></td>
                <td><?= $transaction["shares"] ?></td>
                <td>$<?= $transaction["price"] ?></td>
            </tr>
        <?php endforeach ?>
    </tbody>
</table>