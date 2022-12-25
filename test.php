<html>
  <head>
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/css/bootstrap.min.css" rel="stylesheet">
  <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/js/bootstrap.bundle.min.js"></script>
  <style>
    .dropbtn {
        background-color: #04AA6D;
        color: white;
        padding: 12px;
        font-size: 12px;
        border: none;
    }

    .dropdown {
        position: relative;
        display: inline-block;
    }

    .dropdown-content {
        display: none;
        position: absolute;
        background-color: #f1f1f1;
        min-width: 160px;
        box-shadow: 0px 8px 16px 0px rgba(0,0,0,0.2);
        z-index: 1;
    }

    .dropdown-content p {
        color: black;
        padding: 12px 16px;
        text-decoration: none;
        display: block;
    }

    .dropdown-content p:hover {background-color: #ddd;}

    .dropdown:hover .dropdown-content {display: block;}

    .dropdown:hover .dropbtn {background-color: #3e8e41;}

  </style>
  </head>
  <body>
   <div class="container">
    <h2>Data from the Dashboard</h2>
    <p>Displaying the data from the table</p>            
    <div class="row">
        <?php
            $host='localhost';
            $db_name='bits';
            $username='root';
            $password='2022Root';

            try {
                $con=new PDO("mysql:host={$host};dbname={$db_name}",$username,$password);
            } catch (PDOException $exception) {
                echo 'Connection Error';
            }

            $sql='select * from dashboard1';
            $sqlcall=$con->prepare($sql);
            $sqlcall->execute();
            while($result=$sqlcall->fetch(PDO::FETCH_ASSOC)){
                if ($result['status']==0){ 
        ?>
                    <div class="col-sm-3">
                        <div class="card bg-success text-white">
                            <div class="card-body">
                                Latitude: <?php echo $result['latitude']; ?> <br/>
                                Longitude: <?php echo $result['longitude'];?> <br/> <br/>
                                <div class="dropdown">
                                    <button class="dropbtn">know more</button>
                                    <div class="dropdown-content">
                                        <p>Name: <?php echo $result['owner'];?></p>
                                        <p>No: <?php echo $result['ownerno'];?></p>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
        <?php
            } else if($result['status']==1) {
        ?>
                    <div class="col-sm-3">
                        <div class="card bg-danger text-white">
                            <div class="card-body">
                                Latitude: <?php echo $result['latitude']; ?> <br/>
                                Longitude: <?php echo $result['longitude'];?> <br/> <br/>
                                <div class="dropdown">
                                    <button class="dropbtn">know more</button>
                                    <div class="dropdown-content">
                                        <p>Name: <?php echo $result['owner'];?></p>
                                        <p>No: <?php echo $result['ownerno'];?></p>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
        <?php
            }
        }
        ?>
    </div>
</body>
</html>