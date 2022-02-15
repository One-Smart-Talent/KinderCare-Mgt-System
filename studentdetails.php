<?php include("server.php") ;
 include_once("navbar.php");

;?>

<!DOCTYPE html>
<html lang="en">
<head>
 <meta charset="UTF-8">
 <meta http-equiv="X-UA-Compatible" content="IE=edge">
 <meta name="viewport" content="width=device-width, initial-scale=1.0">
 <link rel="stylesheet" href="./css/home.css"/>
 <title>Student Details</title>
 <style>
  .form-controll{
display: flex;text-align:center; align-items:center;
justify-content: space-between;
  }
 </style>
</head>
<body >
 <div class="containerr" style="display: flex;flex-wrap: wrap;">
 <?php
$query = "SELECT * FROM register";
$result = $db->query($query);
if ($result->num_rows > 0) {
  while ($auction = $result->fetch_assoc()):?>
  <div class = ""  style="background-color: white; height: 300px;; width:350px; float:center; margin:auto; border-radius:10px; padding:20px; margin-bottom:20px;">
  <form>
   <div class="form-controll" >
    <label>Id:</label>
    <input type="text" value="<?= $auction['id']?>">
   </div>
    <div class="form-controll" >
    <label>FirstName:</label>
    <input type="text" value="<?= $auction['firstname']?>">
   </div> <div class="form-controll" >
    <label>Last Name:</label>
    <input type="text" value="<?= $auction['lastname']?>">
   </div><div class="form-controll">
    <label>Phone Number:</label>
    <input type="text" value="<?= $auction['phonenumber']?>">
   </div>

   <div class="form-controll">
    <label>Usercode:</label>
    <input type="text" value="<?= $auction['usercode']?>">
   </div> <div class="form-controll">
    <label>status:</label>
    <input type="text" value="<?= $auction['status']?>">
   </div>
    </div> 
    
  </form>

  <?php
  endwhile;
}
?>
</div>

</body>
</html>