<?php

// autoload_static.php @generated by Composer

namespace Composer\Autoload;

class ComposerStaticInit42eecb2ea7e3c66ece3f6a476fce8ae3
{
    public static $files = array (
        '5255c38a0faeba867671b61dfda6d864' => __DIR__ . '/..' . '/paragonie/random_compat/lib/random.php',
        '7f939cf3886f8168713c84dc1019984a' => __DIR__ . '/..' . '/lastguest/murmurhash/murmurhash3.php',
        '7cfce27594bbc1dd0dbf7e3eb5cd4911' => __DIR__ . '/..' . '/bitwasp/bitcoin/src/Script/functions.php',
    );

    public static $prefixLengthsPsr4 = array (
        'M' => 
        array (
            'Mdanter\\Ecc\\' => 12,
        ),
        'F' => 
        array (
            'FG\\' => 3,
        ),
        'C' => 
        array (
            'Composer\\Semver\\' => 16,
        ),
        'B' => 
        array (
            'BitWasp\\Buffertools\\' => 20,
            'BitWasp\\Bitcoin\\' => 16,
        ),
    );

    public static $prefixDirsPsr4 = array (
        'Mdanter\\Ecc\\' => 
        array (
            0 => __DIR__ . '/..' . '/mdanter/ecc/src',
        ),
        'FG\\' => 
        array (
            0 => __DIR__ . '/..' . '/fgrosse/phpasn1/lib',
        ),
        'Composer\\Semver\\' => 
        array (
            0 => __DIR__ . '/..' . '/composer/semver/src',
        ),
        'BitWasp\\Buffertools\\' => 
        array (
            0 => __DIR__ . '/..' . '/bitwasp/buffertools/src/Buffertools',
        ),
        'BitWasp\\Bitcoin\\' => 
        array (
            0 => __DIR__ . '/..' . '/bitwasp/bitcoin/src',
        ),
    );

    public static $prefixesPsr0 = array (
        'P' => 
        array (
            'Pleo' => 
            array (
                0 => __DIR__ . '/..' . '/pleonasm/merkle-tree/src',
            ),
        ),
    );

    public static $classMap = array (
        'Composer\\InstalledVersions' => __DIR__ . '/..' . '/composer/InstalledVersions.php',
    );

    public static function getInitializer(ClassLoader $loader)
    {
        return \Closure::bind(function () use ($loader) {
            $loader->prefixLengthsPsr4 = ComposerStaticInit42eecb2ea7e3c66ece3f6a476fce8ae3::$prefixLengthsPsr4;
            $loader->prefixDirsPsr4 = ComposerStaticInit42eecb2ea7e3c66ece3f6a476fce8ae3::$prefixDirsPsr4;
            $loader->prefixesPsr0 = ComposerStaticInit42eecb2ea7e3c66ece3f6a476fce8ae3::$prefixesPsr0;
            $loader->classMap = ComposerStaticInit42eecb2ea7e3c66ece3f6a476fce8ae3::$classMap;

        }, null, ClassLoader::class);
    }
}
