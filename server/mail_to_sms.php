<?PHP

//  print "Working ...";
  if (!isset($_GET['cmd_sel'])) die();
  if (!isset($_GET['who_sel'])) die();
  if (!isset($_GET['msg_sel'])) die();

  $cmd_sel = $_GET['cmd_sel'];
  $who_sel = $_GET['who_sel'];
  $msg_sel = $_GET['msg_sel'];
  
  $who = "antonio.asaro@amd.com";
  $sub = "From Antonio's pebble ...";
  $frm = "4165621384@sms.rogers.com";
  $hdr = "From: ".$frm;

  if (strcmp($who_sel, "1")==0) { $who = "4165621384@sms.rogers.com"; }		// Antonio
  if (strcmp($who_sel, "2")==0) { $who = "4162713650@sms.rogers.com"; }		// Lori	
  if (strcmp($who_sel, "3")==0) { $who = "4167974863@sms.rogers.com"; }		// Natalie	
  if (strcmp($who_sel, "4")==0) { $who = "4168804473@@msg.koodomobile.com"; }	// Vince	
  if (strcmp($who_sel, "5")==0) { $who = "4164180128@sms.rogers.com"; }		// Dave	
  if (strcmp($who_sel, "6")==0) { $who = "tpers@antelsystems.com";    }		// Tim	

  $msg = "Press and hold 416-562-1384 to reply\r\n";
  $msg = $msg . "------------------------------\r\n";
  if (strcmp($msg_sel, "1")==0) { $msg = $msg . "Busy, call you later.\r\n"; }
  if (strcmp($msg_sel, "2")==0) { $msg = $msg . "Sounds good. :)\r\n"; }
  if (strcmp($msg_sel, "3")==0) { $msg = $msg . "No thanks.\r\n"; }
  if (strcmp($msg_sel, "4")==0) { $msg = $msg . "Running late ...\r\n"; }
  if (strcmp($msg_sel, "5")==0) { $msg = $msg . "On my way home.\r\n"; }
  if (strcmp($msg_sel, "6")==0) { $msg = $msg . "Just a sec.\r\n"; }
  $msg = $msg . "------------------------------\r\n";


  $sentOK = 0;
  if (strcmp($cmd_sel, "send")==0) {
    if (mail($who, $sub, $msg, $hdr)) { $sentOK = 1; }
  } else {
    print "<b>To:</b> ".$who."<br><b>From:</b> ".$frm."<br><b>Subject:</b> ".$sub."<br><b>Msg:</b> ".$msg."<br><br>";
  }
  $result[1] = array();
  $result[1] = array('I', $sentOK);
  print json_encode($result);

?>





