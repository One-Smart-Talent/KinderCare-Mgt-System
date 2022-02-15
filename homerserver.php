<?php 

include_once('server.php');

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

//Deactivate
if (isset( $_POST['remove-d'])) {
$usercodeDeactivate = $_POST['usercode-d'];
mysqli_query($db,"UPDATE `register`  SET status='activate' WHERE `register`.`usercode` = '$usercodeDeactivate';");

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
?>

