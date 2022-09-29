<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8"/>
	<meta name="viewport" content="width=device-width, initial-scale=1"/>
	<title>WebProgramming Project</title>

	 <style>
		*{
			margin: 0, padding: 0;
		}

		a{text-decoration: none;}

		li{list-style: initial;}

		body{
			width : 960px;
			margin: 0 auto;
			background: white;
		}

		#page-wrapper{
			background: lightgray;
			margin :40px 0;
			padding: 10px 20px;
			border-radius: 5px;
			box-shadow: white;
		}

		header {
	        background-color: white;
	        height: 700px;
	        padding: 100px;
      	}

		main { padding-bottom: 100px; }

		section {
	        display: flex;
	        justify-content: space-between;
	        padding: 5%;
      	}

      	section div {
	        background-color: white;
	        width: 100%;
	        height: 500px;
      	}

		.sa {
	        opacity: 0;
	        transition: all .5s ease;
      	}

      	.sa-scaleUp {
        	transform: scale(.5);
        }

        .sa.show {
	        opacity: 1;
	        transform: none;
      	}

		#main-header{
			padding :40px 50px
		}

		#main-navigation{
			border-top : 1px soid #C8C8C8;
			border-bottom: 1px soid #C8C8C8;
			margin-bottom: 20px;
			height: 40px;
		}

		.outer-menu-item{
			display: inline-block;
			position: relative;
			left: 225px;
		}

		.outer-menu-item:hover{
			background: white;
			color: black;
		}

		table {
			width : 105%;
			border : 10px solid gray;
			border-collapse : collapse;
		}

		th
		{
			padding : 20px;
		}

		td:hover{ background-color : lightsteelblue; }
		
		td{
			padding : 20px;
		}
	</style>

</head>
<body>
	<header>
		<h1><center>20163290 이지호 웹프로그래밍 과제</center></h1>
		<h2><center>Please Scroll Down *^^*</center></h2>
	</header>
	<main>
		<section>
			<div class="sa sa-scaleUp"><center><h1><font size = 50>Compare Your Device</font></h1></center></div>
		</section>
		<section>
			<div class="sa sa-scaleUp"><center><h1><font size = 50>If you choose your Device, I will compare</font></h1></center></div>
		</section>
	</main>
	<script>
      // Scroll Animation (sa, 스크롤 애니메이션)
      const saTriggerMargin = 300;
      const saElementList = document.querySelectorAll('.sa');

      const saFunc = function() {
        for (const element of saElementList) {
          if (!element.classList.contains('show')) {
            if (window.innerHeight > element.getBoundingClientRect().top + saTriggerMargin) {
              element.classList.add('show');
            }
          }
        }
      }

      window.addEventListener('load', saFunc);
      window.addEventListener('scroll', saFunc);
    </script>
	<div id = "page-wrapper">
		<header id = "main-header">
			<hgroup>
				<h1 class = "master-title"><center><font size = 10>Compare Your Device</font></center></h1>
				<h4 class = "master-description"><center>If you choose Your Device, I will compare</center></h4>
			</hgroup>
		</header>
		<nav id = "main-navigation">
			<div class "get-center">
				<ul class = "outer-menu">
					<li class = "outer-menu-item">
						<span class = "menu-title"><center>Phone</center></span>
						<ul class = "inner-menu">
							<li class = "inner-menu-item"><a href="#"><center>Which one do you like?</center></a></li>
						</ul>
					</li>
					<li class = "outer-menu-item">
						<span class = "menu-title"><center>Audio Equipment</center></span>
						<ul class = "inner-menu">
							<li class = "inner-menu-item"><a href="#"><center>I love this one</center></a></li>
						</ul>
					</li>
				</ul>
			</div>
		</nav>
		<div class = "get-middle">
			<form method = "get"> 
					<span class = "search-bar">
					<select name = 'Choose1'>
						<optgroup label = "PHONE">
							<option value = "choose">choose</option>
							<option value = "galaxys21">Galaxy S21</option>
							<option value = "iphone13">Iphone13</option>					
						</optgroup>
					</select>
					</span>
					<span class = "search-bar">
						<select name = 'Choose2'>
							<optgroup label = "PHONE">
								<option value = "choose">choose</option>
								<option value = "galaxyS21">Galaxy S21</option>
								<option value = "iphone13">Iphone13</option>					
							</optgroup>
						</select>
					</span>
					<input type = "submit" value = "확인">
			</form>
		</div>

		<div id = "content">
			<?php
			$conn = mysqli_connect('localhost', 'jiho', '1234', 'phone');
			mysqli_select_db($conn, 'phone');

			$sql = "select * from choose";
			$result = mysqli_query($conn, $sql);
			$count = mysqli_num_fields($result);

			$listl = array();

			if(isset($_GET['Choose1'])){
				$sql = "select * from {$_GET['Choose1']}";
				$result = mysqli_query($conn, $sql);
				$count = mysqli_num_fields($result);
				if($_GET['Choose1'] == "choose"){
					echo "";
				}else{
					$listl[0] = "제품명";
					$listl[1] = "가격";
					$listl[2] = "용량";
					$listl[3] = "제품크기";
					$listl[4] = "무게";
					$listl[5] = "화면크기";
					$listl[6] = "방수/방진";
					$listl[7] = "칩";
					$listl[8] = "배터리지속시간";
					$listl[9] = "배터리 용량";
					$listl[10] = "잠금해제방식";
					$listl[11] = "충전방식";
					$listl[12] = "운영체제";	
				}
			}
			

			?>
				<article>
					<div class="article-header-left"style="width:45%; height:50px; border:1px ; float:left;">
						<?php
							$row = mysqli_fetch_row($result); 
							
							if(isset($_GET['Choose1'])){
								if($_GET['Choose1'] == "choose"){
									echo "";
								}else{
									echo "<h1 class=\"article-body\">{$row[0]}</h1>";
									echo "<img src = \"{$row[13]}\" style=\"width:400px; height: 400px;\">";
								}
							}
							
						?>
							<table>
								<thead>
									<tr><?php
											if(isset($_GET['Choose1'])){
												if($_GET['Choose1'] == "choose"){
													echo "";
												}else{
													echo "<th>항목</th>";
													echo "<th>내용</th>";
												}
											}

										?>
									</tr>
								</thead>
								<tbody>
									<?php
										if(isset($_GET['Choose1'])){
											if($_GET['Choose1'] == "choose"){
												echo "";
											}else{
												for($i=0; $i<13; $i++){
													echo "<tr>";
													echo "<td>$listl[$i]</td>";
													echo "<td>$row[$i]</td>";
													echo "</tr>";
												}
											}									
										}
									?>
									</td>
						        </tbody>
						    </table>
					</div>
				</article>
		</div>
		<div id = "content">

			<?php
			$conn = mysqli_connect('localhost', 'jiho', '1234', 'phone');
			mysqli_select_db($conn, 'phone');

			$sql = "select * from choose";
			$result = mysqli_query($conn, $sql);
			$count = mysqli_num_fields($result);

			$listl = array();

			if(isset($_GET['Choose2'])){
				$sql = "select *from {$_GET['Choose2']}";
				$result = mysqli_query($conn, $sql);
				$count = mysqli_num_fields($result);
				if($_GET['Choose2'] == "choose"){
					echo "";
				}else{
					$listl[0] = "제품명";
					$listl[1] = "가격";
					$listl[2] = "용량";
					$listl[3] = "제품크기";
					$listl[4] = "무게";
					$listl[5] = "화면크기";
					$listl[6] = "방수/방진";
					$listl[7] = "칩";
					$listl[8] = "배터리지속시간";
					$listl[9] = "배터리 용량";
					$listl[10] = "잠금해제방식";
					$listl[11] = "충전방식";
					$listl[12] = "운영체제";
				}
			}

			?>
				<article>
					<div class="article-header-right" style="width:45%; height:50px; border:1px ; float:right;">
						<?php
							$row = mysqli_fetch_row($result); 

							if(isset($_GET['Choose2'])){
								if($_GET['Choose2'] == "choose"){
									echo "";
								}else{
									echo "<h1 class=\"article-body\">{$row[0]}</h1>";
							 		echo "<img src = \"{$row[13]}\" style=\"width:400px; height: 400px;\">";
							 	}
							}

						?>
						<table>
							<thead>
								<tr>
									<?php

										if(isset($_GET['Choose2'])){
											if($_GET['Choose2'] == "choose"){
												echo "";
											}else{
												echo "<th>항목</th>";
												echo "<th>내용</th>";
											}
										}

									?>
								</tr>
							</thead>
							<tbody>
								
								<?php
									if(isset($_GET['Choose2'])){
										if($_GET['Choose2'] == "choose"){
											echo "";
										}else{
											for($i=0; $i<13; $i++){
												echo "<tr>";
												echo "<td>$listl[$i]</td>";
												echo "<td>$row[$i]</td>";
												echo "</tr>";
											}
										}
									}
								?>								
					        </tbody>
					    </table>
					</div>
				</article>
		</div>
	</div>
</body>

</html>
