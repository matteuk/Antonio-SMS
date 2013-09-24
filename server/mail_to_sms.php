<?PHP
  print "It works!!<br>";
  if !isset($_GET['send']) die();

  $to = "antonio@antonioasaro.site50.net";
//  $to = "4165621384@sms.rogers.com";
  $subject = "testing ...";
  $message = "I hope this works.";
  $headers = "From: Antonio's pebble";

  $sentOK = mail($to, $subject, $message, $headers);
  print "sentOK = " . $sentOK;
?>
