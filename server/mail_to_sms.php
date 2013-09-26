<?PHP

//  print "Working ...<br>";
  if (!isset($_GET['cmd'])) die();
  if (!isset($_GET['who'])) die();
  if (!isset($_GET['msg'])) die();

  $cmd = $_GET['cmd'];
  $who = $_GET['who'];
  $msg = $_GET['msg'];
  
  $sub = "From Antonio's pebble ...";
  $frm = "4165621384@sms.rogers.com";
  $hdr = "From: ".$frm;

  $msg = "------------------------------\r\n" . $msg;
  $msg = "Press and hold 416-562-1384 to reply\r\n" . $msg;
  $msg = $msg . "------------------------------\r\n";

  $sentOK = 0;
  if (strcmp($cmd, "send") == 0) {
      if (mail($who, $sub, $msg, $hdr)) { $sentOK = 1; }
  } else {
      if (strcmp($cmd, "test") == 0) {
        print "<b>To:</b> ".$who."<br><b>From:</b> ".$frm."<br><b>Subject:</b> ".$sub."<br><b>Msg:</b> ".$msg."<br><br>";
    }
  }
  $result[1] = array();
  $result[1] = array('I', $sentOK);
  print json_encode($result);

?>

