<!DOCTYPE html>
<html>
<head>
	<title>Highscores</title>
	<link rel="stylesheet" href="css/stylesheet.css">
	<link href="https://fonts.googleapis.com/css?family=Open+Sans" rel="stylesheet">
	<link href="https://fonts.googleapis.com/css?family=Roboto" rel="stylesheet">
</head>
<body>
	<div class="wrapper">
		<h1 class="title">Highscores</h1>
		<?php 
			require_once("config.php");

			$link = mysqli_connect(
				HOST, 
				DB_USER,
				DB_PASS,
				DB_NAME
			);	

			if ($link->connect_errno)
			{
				echo "Could not connect to database";
				exit();
			} 

			$query = "SELECT * FROM " . HIGHSCORES_TABLE . " ORDER BY score DESC";
			$result = $link->query($query);

			if ($result->num_rows > 0)
			{
				$i = 1;
				while($row = mysqli_fetch_array($result))
				{
					echo '<div class="hs_row">';
					echo '<p class="hs_id">'.$i.'.</p>';
					echo '<p class="hs_name">'.$row["name"].'</p>';
					echo '<p class="hs_score">'.$row["score"].'</p>';
					//echo '<p class="hs_time">'.$row["timestamp"].'</p>';
					echo '</div>';

					$i++;
				}
			}
		?>	
	</div>
</body>
</html>