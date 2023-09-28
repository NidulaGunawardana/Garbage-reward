

<?php

require "connection.php";


date_default_timezone_set('Asia/Colombo');
$d = date("Y-m-d");
$t = date("H:i:s");



if (!empty($_POST['mobile']) && !empty($_POST['reward'])) {
    $mobile = $_POST['mobile'];
    $reward = $_POST['reward'];


    $user_search = Database::s("SELECT * FROM `user` WHERE `mobile_no` = '" . $mobile . "';");
    if ($user_search->num_rows != 1) {
        
        Database::iud("INSERT INTO `user`(`mobile_no`) VALUES('" . $mobile . "');");

        $user_search_new = Database::s("SELECT * FROM `user` WHERE `mobile_no` = '" . $mobile . "';");
        $userid_dat_new = $user_search_new->fetch_assoc();
        $userid_new = $userid_dat_new['id'];
        Database::iud("INSERT INTO `rewards`(`user_id`,`reward`,`date`) VALUES('".$userid_new."','".$reward."','".$d."');");
        echo "New user added and stored reward";

    } else {
        $userid_dat = $user_search->fetch_assoc();
        $userid = $userid_dat['id'];
        Database::iud("INSERT INTO `rewards`(`user_id`,`reward`,`date`) VALUES('".$userid."','".$reward."','".$d."');");
        echo "reward added";
    }

}






?>