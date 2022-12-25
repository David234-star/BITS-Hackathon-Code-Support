<html>
  <head>
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/css/bootstrap.min.css" rel="stylesheet">
  <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/js/bootstrap.bundle.min.js"></script>
  </head>
  <body>
   <div class="container">
    <h2>Data from the Dashboard</h2>
    <p>Displaying the data from the table</p>            
    <table class="table table-bordered">
     <thead>
        <tr>
        <th>id</th>
        <th>latitude</th>
        <th>longitude</th>
        <th>owner</th>
        <th>ownerno</th>
        <th>status</th>
     </thead>
     <tbody>
        <?php
            $host='localhost';
            $db_name='bits';
            $username='root';
            $password='2022Root';

            try {
                $con=new PDO("mysql:host={$host};dbname={$db_name}",$username,$password);
                echo 'Success with Database Connection';
            } catch (PDOException $exception) {
                echo 'Connection Error';
            }

            $sql='select * from dashboard1';
            $sqlcall=$con->prepare($sql);
            $sqlcall->execute();
            echo '<br/>';
            while($result=$sqlcall->fetch(PDO::FETCH_ASSOC)){
        ?>
                <tr>
                    <td><?php echo $result['id'];?></td>
                    <td><?php echo $result['latitude'];?></td>
                    <td><?php echo $result['longitude'];?></td>
                    <td><?php echo $result['owner'];?></td>
                    <td><?php echo $result['ownerno'];?></td>
                    <td><?php 
                            if ($result['status']==1){
                                echo 'alert occured'; 
                        ?>
                        <?php
                            } else {
                                echo 'normal';
                            }
                        ?>
                    </td>
                </tr>
        <?php
            }
        ?>
    </div>
</tbody>
</body>
</html>