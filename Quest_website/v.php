<html>
<head>    
<meta charset="utf-8" /> 
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
  <title>BirthDay_Quest_page2</title>
</head>
<body style="background-color: FFFF00; width: 200"> 

<?php
   if (isset($_POST['press'])){
	   if ($_POST['1code'] == 'BdQu3FS' && $_POST['2code'] == 'bDq1tYH' && $_POST['3code'] == 'BdqR4iM' && $_POST['4code'] == 'bdQ7hwX'){
			echo '<h4 style="text-align: center; color: red">Коди вірні</br>Агент чекає на вас за координатами:</br>50.448147,30.479219</h1><br>';
	   }else if ($_POST['1code'] == '' && $_POST['2code'] == '' && $_POST['3code'] == '' && $_POST['4code'] == ''){
			echo '<h4 style="text-align: center; color: red">Помилка. Деякі з полів пусті:(</h4><input type="button" onclick="history.back()" value="Назад">';
	   }else{	
		echo '<h4 style="text-align: center; color: red">Коди не вірні:(</br>Спробуйте ще раз </h1><input type="button" onclick="history.back()" value="Назад">';	   
	   }
   }
?>

</body>    
</html>