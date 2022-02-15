<?php
include_once('server.php');
?>

<!DOCTYPE html>
<html lang="en">
<head>
 <meta charset="UTF-8">
 <meta http-equiv="X-UA-Compatible" content="IE=edge">
 <meta name="viewport" content="width=device-width, initial-scale=1.0">
 <title>Document</title>
</head>
<body>
 <?php
if (isset($_POST['add-view'])){
$name_g = $_POST['name-g'];
$query = "SELECT * FROM `grades` WHERE `name` = '$name_g';";
$result = mysqli_query($db,$query);

if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
     // echo "<a href="viewGrades.php">View Grades</a>";
        echo "id: " . $row["id"]. " - Name: " . $row["name"]. " " . $row["studentscore"]. "<br>";
    }
} else {
    echo "0 results";
}
$db->close();

}
?>

</body>
</html>