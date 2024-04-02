<?php

require_once 'model.php';
require_once 'vendor/autoload.php'; 
use BitcoinPHP\BitcoinECDSA\BitcoinECDSA;

class Wallet {

    public static function createWallet($uuid) {
        $bitcoinECDSA = new BitcoinECDSA();
        $bitcoinECDSA->generateRandomPrivateKey();
        $privateKey = $bitcoinECDSA->getPrivateKey();
        $publicKey = $bitcoinECDSA->getAddress();
        
        $pdo = Model::getPdo();
        $stmt = $pdo->prepare("INSERT INTO wallet (uuid, privateKey, publicKey) VALUES (:uuid, :privateKey, :publicKey)");
        $stmt->bindParam(':uuid', $uuid);
        $stmt->bindParam(':privateKey', $privateKey);
        $stmt->bindParam(':publicKey', $publicKey);

        $stmt->execute();

        return $stmt->execute() ? true : false;
    }   


    public static function getUuidPublicKey($uuid){
        $pdo = Model::getPdo();
        $stmt = $pdo->prepare("SELECT publicKey FROM wallet WHERE uuid = :uuid");
        $stmt->bindParam(':uuid', $uuid);
        $stmt->execute();
        $result = $stmt->fetch(PDO::FETCH_ASSOC);
        return $result;
    }
    
    public static function getBalanceFromUuid($publicKey){
        $url = "https://blockchain.info/q/addressbalance/".$publicKey;
        $balance = file_get_contents($url);
        return $balance;
    }
}