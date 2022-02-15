<?php
   include_once("navbar.php");
   include_once('server.php');
   include_once('homerserver.php');
?>

<!DOCTYPE html>
<html lang=" en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="./css/home.css"/>
    <title>Home</title>

</head>
<body>
    
<div class="container">
<div class="row row1" style="text-align: center;">
  <div class="col-sm-4">
     <div class="login-container">
          <form class="ui form" method="post" action="home.php">
			    <legend>View Grades</legend>
            <div class="field">
              <label >Name</label>
              <input type="text" name="name-g" placeholder="Name" />
            </div>
            <div class="field">
              <label>Student ID</label>
              <input type="text" name="score" placeholder="Id" />
            </div>
            <button class="ui button" type="submit" name="add-view">View Grades</button>
          </form>
        </div>
         <?php
if (isset($_POST['add-view'])){
$name_g = $_POST['name-g'];
$query = "SELECT * FROM `grades` WHERE `name` = '$name_g';";
$result = $db->query($query);
if ($result->num_rows > 0) {
  while ($auction = $result->fetch_assoc()):?>
  <div class = ""  style="background-color: white; height:100%; width:200px; float:center; margin:auto; border-radius:10px; padding:10px; margin-bottom:20px">
    <h4 style="color:black">Name: <?= $auction['name']?></h4>
    <h4 style="color:black">Score: <?= $auction['studentscore']?></h4>

  </div>
  <?php
  endwhile;
}}
?>
  </div>
<div class="col-sm-4">
<div class="login-container">
<form class="ui form" method= "post" action = "home.php">
	<legend>Add Assignment</legend>
  <div class="field">
  <label>Letters</label> 
		<input type="text" name="letters"/>
		</div>
        <div class="field">
			<label >Start time</label> 
		<input type="text" name="start_time" />
		</div>		
           <div class="field">
			<label >End time</label> 
      <input type="text" name="end_time" />
		</div>
       <div class="field">
			<label >Date</label> 
      <input type="date" name="assgn_date" />
		</div>
					<button id="submit" name="insert"> Add </button>
			</form>
  </div>
  </div>
 

  <div class="col-sm-4">
<div class="login-container">
<form class="ui form" method= "post" action = "home.php" >
			<!-- Form Name -->
			<legend>Deactivate student</legend>
        <div class="field">
			<label>Usercode</label> 
		<input type="text" name="usercode-d"/>
    </div>
    <button class="ui button" type="submit" name="remove-d" style="margin: 30px 20px;">Deactivate</button>

</form>
  </div>
  </div>
  
 </div>
<div class="row row2" style="text-align: center;">
 <div class="col-sm-4">
     <div class="login-container">
          <form class="ui form" method="post" action="home.php">
			<legend> Student</legend>
            <div class="field">
              <label >Description</label>
              <input type="text" name="usercode-d" placeholder="Description"/>
            </div>
            <button class="ui button" type="submit" name="add-report">Add Report</button>
          </form>
        </div>
  </div>
    <div class="col-sm-4">
     <div class="login-container">
          <form class="ui form" method="post" action="home.php">
			<legend>Register Pupil</legend>
            <div class="field">
              <label >First Name</label>
              <input type="text" name="first-name" placeholder="First Name" />
              <span class="text-danger"><?php if (isset($name_error)) echo $name_error; ?></span>
            </div>
            <div class="field">
              <label>Last Name</label>
              <input type="text" name="last-name" placeholder="Last Name" />
              <span class="text-danger"><?php if (isset($last_error)) echo $last_error; ?></span>

            </div>
            <div class="field">
          <label>Phone Num</label>
          <input type="number" name="phone-number" placeholder="Phone Number" />

        </div>
         <div class="field">
          <label>User Code</label>
          <input type="number" name="usercode" placeholder="Usercode" />
              <span class="text-danger"><?php if (isset($usercode_er)) echo $usercode_er; ?></span>

        </div>
            
            <button class="ui button" type="submit" name="registerBtn">Register Student</button>
          </form>
        </div>
  
  </div>
   <div class="col-sm-4">
     <div class="login-container">
          <form class="ui form" method="post" action="home.php">
			<legend>Reactivate Student</legend>
            <div class="field">
              <label >UserCode</label>
              <input type="text" name="usercode-d" placeholder="Desc" />
            </div>           
            <button class="ui button" type="submit" name="add-comment">Reactivate</button>
          </form>
        </div>
  
  </div>
</div>
</div>
  </body>
