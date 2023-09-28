
<?php

require "connection.php";

$mobile = $_GET["mobile"];

$reward = 0;

$dev = Database::s("SELECT * FROM `rewards` INNER JOIN `user` ON `rewards`.`user_id` = `user`.`id` WHERE `user`.`mobile_no` = '" . $mobile . "';");
if ($dev->num_rows > 0) {
    for ($i = 0; $i < $dev->num_rows; $i++) {
        $dat = $dev->fetch_assoc();
        $reward = $reward + (float)$dat['reward'];
    }
    echo json_encode(array("reward"=>$reward));
} else {
    echo "No user";
}



?>