<?php 

header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Headers: access");
header("Access-Control-Allow-Methods: POST");
header("Access-Control-Allow-Credentials: true");

require_once("config.php");

$name;
$score;

if (isset($_GET["name"]) 
	&& isset($_GET["score"]))
{
	if (is_numeric($_GET["score"]))
	{
		$name = $_GET["name"];
		$score = $_GET["score"];

		echo $name;
		echo $score;

		$link = mysqli_connect(
			HOST,
			DB_USER,
			DB_PASS,
			DB_NAME
		);

		$rowcount = $link->query("SELECT * FROM ".HIGHSCORES_TABLE);
		$rows = $rowcount->num_rows + 1;

		$query = "INSERT INTO highscores (id, name, score, timestamp) VALUES ('".$rows."','".$name."','".$score."', CURRENT_TIMESTAMP)";
		$result = $link->query($query);

		if ($result)
		{
			echo "Inserted";
		}
		else
		{
			echo "Didn't work";
		}
	}
	else
	{
		echo "Score must be an integer";
	}
}
else
{
	echo "Missing parameters";
}

?>