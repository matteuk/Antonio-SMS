<?PHP

  print "It works!!<br>";
  if (!isset($_GET['cmd_sel'])) die();
  if (!isset($_GET['who_sel'])) die();
  if (!isset($_GET['msg_sel'])) die();

  $cmd_sel = $_GET['cmd_sel'];
  $who_sel = $_GET['who_sel'];
  $msg_sel = $_GET['msg_sel'];
  
  $who = "antonio@antonioasaro.site50.net";
  $msg = "Test msg";
  if (strcmp($who_sel, "1")==0) { $who = "4165631384"; }	// Antonio
  if (strcmp($who_sel, "2")==0) { $who = "4162713650"; }	// Lori	

  if (strcmp($msg_sel, "1")==0) { $msg = "OK"; }
  if (strcmp($msg_sel, "2")==0) { $msg = "Call you later"; }

  $sub = "Reply msg from Antonio";
  $hdr = "From: My_pebble";

  if (strcmp($cmd_sel, "send")==0) {
    print "<br>Sending email ...";
    print "<br><b>To:</b> ".$who."; <b>From:</b> ".$hdr."; <b>Subject:</b> ".$sub."; <b>Msg:</b> ".$msg;
//    $sentOK = mail($who, $sub, $msg, $hdr);
  }
  print "<br>sentOK = " . $sentOK;

?>
