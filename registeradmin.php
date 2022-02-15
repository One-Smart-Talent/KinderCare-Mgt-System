<?php   include_once("header.php");
?>


<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title> Register</title>
<link href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" rel="stylesheet">
<link
      rel="stylesheet"
      href="https://cdnjs.cloudflare.com/ajax/libs/semantic-ui/2.4.1/semantic.min.css"
      integrity="sha512-8bHTC73gkZ7rZ7vpqUQThUDhqcNFyYi2xgDgPDHc+GXVGHXq+xPjynxIopALmOPqzo9JZj0k6OqqewdGO3EsrQ=="
      crossorigin="anonymous"
      referrerpolicy="no-referrer"
    />
    <link rel="stylesheet" href="./css/register.css"/>
</head>
<body>
  <nav class="navbar navbar-default navbar-static-top">
	  <div class="cont">
	  <h3 style="color: black; text-align:left; padding:10px 0px 10px 30px">KINDERCARE SYSTEM</h3>
	  </div>
	</nav>

<div class="form-container">
  <h4 style="color: white; text-align:center;">New Teacher Registration</h4>
<form class="ui form" action="register.php" method="post">
	<?php include('errors.php'); ?>
<div class="field">
<label>Name</label>
<input type="text" name="username" class="form-control"/>
</div>
<div class="field ">
<label>Email</label>
<input type="email" name="email" class="form-control" />
</div>
<div class="field">
<label>Password</label>
<input type="password" name="password" class="form-control"/>
</div>  
<div lass="field">
<label>Confirm Password</label>
<input type="password" name="cpassword" class="form-control" />
</div>
<input type="submit" class="btn btn-primary" name="signup" value="submit">
<p>Already admin? <a href="login.php">Sign in</a></p>

</form>
</div>

</body>
