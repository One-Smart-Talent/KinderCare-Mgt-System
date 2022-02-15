<?php 
session_start();
// connect to database
$db = mysqli_connect('localhost', 'root', 'Wisepro25*', 'kindercare');

// variable declaration
$username = "";
$email    = "";
$message="";

$error   = array(); 

// call the login() function if register_btn is clicked
if (isset($_POST['login_btn'])) {
	login();
}

// LOGIN USER
function login(){
	global $db, $username, $message;
 $error = array(); 
	// grap form values
	$username = $_POST['username'];
	$password = $_POST['password'];
	// attempt login if no errors on form
	if (count($error) == 0) {
		$password = md5($password);

		$query = "SELECT * FROM users WHERE username='$username' AND password='$password' LIMIT 1";
		$results = mysqli_query($db, $query);

		if (mysqli_num_rows($results) == 1) { // user found
			// check if user is admin or user
			 
			$row = mysqli_fetch_assoc($results);
		$_SESSION["id"] = $row['id'];
   $_SESSION["name"] = $row['username'];
			if(isset($_SESSION["id"])) {
    header("Location:home.php?success");
    }else{
					echo "Invalid Username or Password!";
				}
		}else {
			array_push($error, "Wrong username or password");
		}
	}
	
}

//Register Student
	if (isset($_POST['registerBtn'])) {
	$firstname    =  $_POST['first-name'];
	$lastname       =  $_POST['last-name'];
	$phoneNumber  =  $_POST['phone-number'];
	$usercode =  $_POST['usercode'];
if (!preg_match("/^[a-zA-Z ]+$/",$firstname)) {
$name_error = "Name must contain only alphabets and space";
}
if (!preg_match("/^[a-zA-Z ]+$/",$lastname)) {
$last_error = "Name must contain only alphabets and space";
}
if(strlen($phoneNumber > 10)){
	$mobile_error = "Number should be less than 10 characters";
}
if(strlen($usercode) < 6) {
$usercode_er = "UserCode must be minimum of 6 characters";
} 

if (!$error) {
$usedcode = mysqli_query($db, "SELECT  usercode FROM register;");
	if($usercode != $usedcode){
		if(mysqli_query($db, "INSERT INTO register(firstname, lastname,phonenumber,status, usercode) VALUES('" . $firstname . "', '" . $lastname . "','" . $phoneNumber . "', '" . 'active' . "','" . $usercode . "')")) {
header("location: home.php?success");
} else {
echo "Error:" . mysqli_error($db);
}
	}
	else{
	echo "code already used";
	}  
}
mysqli_close($db);
}

//comment
	if (isset($_POST['add-comment'])) {
$comment = $_POST['comment'];
mysqli_query($db, "INSERT INTO comments(comment) VALUES('" . $comment . "')");
	
header("Location: home.php?success");
}
//assignment\
if (isset( $_POST['insert'])) {
$letters =$_POST['letters'];
$start_time = $_POST['start_time'];
$end_time = $_POST['end_time'];
$assgn_date = $_POST['assgn_date'];

mysqli_query($db, "INSERT INTO assignments(letter, startime, endtime, assigDate) VALUES('" . $letters . "','" . $start_time . "','" . $end_time . "','" . $assgn_date . "')");

header("Location: home.php?success");
}
//Deactivate
if (isset( $_POST['remove-d'])) {
$usercodeDeactivate = $_POST['usercode-d'];
mysqli_query($db,"UPDATE `register`  SET status='deactivated' WHERE `register`.`usercode` = '$usercodeDeactivate';");

header("Location: home.php?success");
}

//Report
if (isset( $_POST['add-report'])) {
$usercodeDeactivate = $_POST['usercode-d'];
mysqli_query($db,"INSERT INTO report(report) VALUES ('$usercodeDeactivate' );");

header("Location: home.php?success");
}

