<?php
// WordPress Configuration

// Load environment variables
$env_mysql_db   = getenv('MYSQL_DATABASE') ?: 'wordpress';
$env_mysql_user = getenv('MYSQL_ADMIN') ?: 'admin_user';

// Load password from admin secret
$env_mysql_password_file = '/run/secrets/db_password';
$env_mysql_password = file_exists($env_mysql_password_file) ? trim(file_get_contents($env_mysql_password_file)) : '';

define('DB_NAME', $env_mysql_db);
define('DB_USER', $env_mysql_user);
define('DB_PASSWORD', $env_mysql_password);
define('DB_HOST', getenv('WORDPRESS_DB_HOST') ?: 'mariadb:3306');
define('DB_CHARSET', 'utf8mb4');
define('DB_COLLATE', '');

// Security keys (replace with real unique phrases)
define('AUTH_KEY', 'CMWjdoV%9{Nlv;9Noi$)KN)BB.Jr$XXven|~q|{f9!;d|h9o 5&AJ#]sP}>u5m?');
define('SECURE_AUTH_KEY', '|h.P@|}q5/cA [Z5$Zovn@V/3f.TRk|me}gn6]4y3|KS!u4nI!@(3tb=K{-w4FAm');
define('LOGGED_IN_KEY', 'T7LTSYeN,eBfxnCz97OjBZ- %B4OIvvMtAPGm8Jxsmm6nm$!6fgd>a]N5h?M8%E');
define('NONCE_KEY', 'U|,tXhUe|*%+r1v}xV8g-z?M~{frB|~<Uk@Kf|u2ZyxMWG-c$7<i2|>R[<_f@_fJ');
define('AUTH_SALT', 'OU8 T>8ec+Si:me-.k;Eww7nXz|s3X!?i8}AO1q(+<+?#P>nF4*U>~;#$P[WpDe');
define('SECURE_AUTH_SALT', '&P1d@.i is^R]Pl.?4vm>D5PqtJZ{txfu!h]Yl:t*As,=1Mc:{n-#GyWMem{a8i?');
define('LOGGED_IN_SALT', 'IQ,GEE&/@o=/ZjQ6HRl5^M=[ 4o9pWlji8Ktk!H&^,w?tG;V_M{zz6OC)PLnpe');
define('NONCE_SALT', '~]Oh};a_hQj-n:tvcBe+WGJGl*7fJmUYy6>?ekQWtMXyzR-ZYj=Zo.Dax152kB');

// Table prefix
$table_prefix  = 'wp_';

// Debug mode
define('WP_DEBUG', false);

// Absolute path to WordPress directory
if ( !defined('ABSPATH') )
    define('ABSPATH', dirname(__FILE__) . '/');

// Include WordPress settings
require_once(ABSPATH . 'wp-settings.php');
