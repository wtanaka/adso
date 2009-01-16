<html>

<head>
  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
  <link rel="stylesheet" href="adso.css" type="text/css" media="screen, projection" />
</head>

<script language="javascript" src="jquery-1.2.2.min.js"></script>
<script language="javascript" src="jquery-1.2.2.hf.js"></script>

<body>


  <div style="float:right" class="test_score"><span class="red"><span id="correct">0</span>/<span id="total">0</span></span></div>
  <img src="logo.gif" />


  <br />

  <div id="question">We are sorry for the problem. Please contact us at service@popupchinese.com</div>
  <div id="answer1" onclick="correct_answer(1)"></div>
  <div id="answer2" onclick="correct_answer(2)"></div>
  <div id="answer3" onclick="correct_answer(3)"></div>
  <div id="answer4" onclick="correct_answer(4)"></div>



<script language="javascript">

  total = 0;
  correctAnswer = 0;
  randomNum = 0;

  var question = new Array();
  var answer1  = new Array();
  var answer2  = new Array();
  var answer3  = new Array();
  var answer4  = new Array();
  var correct  = new Array();

<?php

  // Connect to the Database
  $username = "adso";
  $password = "adso";
  $database = "adso";
  mysql_connect("localhost", $username, $password);
  @mysql_select_db($database) or die ("Unable to select database");

  $user = $argv[1];

  $query = 'SELECT * from questions join users join lessons where questions.lesson_id = lessons.id and lessons.user_id = users.id AND questions.audio = "" and users.username LIKE BINARY "'.$user.'" and lessons.type = "published" and lessons.pubdate < NOW() and questions.question NOT REGEXP "Question";';
  $result =  mysql_query($query);
  $num = mysql_numrows($result);



  // START XML FILE
  for ($i = 0; $i < $num; $i++) { 

    $question       = mysql_result($result, $i, "question");
    $answer1        = mysql_result($result, $i, "answer1");
    $answer2        = mysql_result($result, $i, "answer2");
    $answer3        = mysql_result($result, $i, "answer3");
    $answer4        = mysql_result($result, $i, "answer4");
    $correct        = mysql_result($result, $i, "correct");

    $question = strip_tags($question);
    $answer1  = strip_tags($answer1);
    $answer2  = strip_tags($answer2);
    $answer3  = strip_tags($answer3);
    $answer4  = strip_tags($answer4);

echo '
    question['.$i.'] = "'.str_replace('"','\"',$question).'";
    answer1['.$i.']  = "a) '.str_replace('"','\"',$answer1).'";
    answer2['.$i.']  = "b) '.str_replace('"','\"',$answer2).'";
    answer3['.$i.']  = "c) '.str_replace('"','\"',$answer3).'";
    answer4['.$i.']  = "d) '.str_replace('"','\"',$answer4).'";
    correct['.$i.']  = '.$correct.';
    total++;
';

  }

  mysql_close();

?>
  var this_question_has_been_answered_incorrectly_before = 0;

  getRandomQuestion();

  function getRandomQuestion() {

    prevNum = randomNum;

    for (i = 0; i < 20 && randomNum == prevNum; i++) {
      randomNum = Math.floor(Math.random()*total);
    }

    document.getElementById("question").innerHTML = question[randomNum];
    document.getElementById("answer1").innerHTML  = answer1[randomNum];
    document.getElementById("answer2").innerHTML  = answer2[randomNum];
    document.getElementById("answer3").innerHTML  = answer3[randomNum];
    document.getElementById("answer4").innerHTML  = answer4[randomNum];

    correctAnswer = correct[randomNum];
    this_question_has_been_answered_incorrectly_before = 0;

  }



  function correct_answer(myguess) {

    if (correctAnswer == myguess) {
      greenAnswer = "#answer"+myguess;
      $(greenAnswer).highlightFade({color:'green',speed:2000,iterator:'sinusoidal'});
      setTimeout(getRandomQuestion, 2000);

      if (this_question_has_been_answered_incorrectly_before == 0) {
        var thistotal = document.getElementById("correct").innerHTML;
        tempint = parseInt(thistotal);
        tempint++;
        document.getElementById("correct").innerHTML = tempint;
      }

    } else {
      greenAnswer = "#answer"+myguess;
      $(greenAnswer).highlightFade({color:'red',speed:2000,iterator:'sinusoidal'});
    }
    
    if (this_question_has_been_answered_incorrectly_before == 0) {
      var thistotal = document.getElementById("total").innerHTML;
      tempint = parseInt(thistotal);
      tempint++;
      document.getElementById("total").innerHTML = tempint;
      this_question_has_been_answered_incorrectly_before = 1;
    }

  } 




</script>

</body>
</html>
