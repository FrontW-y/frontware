<?php

require_once 'model.php';
require_once 'vendor/autoload.php'; 

use BitWasp\Bitcoin\Address\PayToPubKeyHashAddress;
use BitWasp\Bitcoin\Key\PrivateKeyFactory;

class BitcoinWallet {

    public static function createWallet($uuid) {
        
        $privateKeyFactory = PrivateKeyFactory::create(true);
        $privateKey = $privateKeyFactory->toWif();
        $publicKey = $privateKeyFactory->getPublicKey();
        $address = new PayToPubKeyHashAddress($publicKey->getPubKeyHash());
        $address = $address->getAddress();
       
        
        
        $pdo = Model::getPdo();
        $stmt = $pdo->prepare("INSERT INTO wallet (uuid, privateKey, publicKey) VALUES (:uuid, :privateKey, :publicKey)");
        $stmt->bindParam(':uuid', $uuid);
        $stmt->bindParam(':privateKey', $privateKey);
        $stmt->bindParam(':publicKey', $address);

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

