<!DOCTYPE html>
<html lang="en">
	<head>
		<title>ImServ</title>
		<script src="jquery.min.js"></script>
		<script src="Bootstrap/js/bootstrap.js"></script>
		<link rel='stylesheet' type='text/css' href='Bootstrap/css/bootstrap.css'>
	</head>
	<?php		
		function btnC() {
			return "Test";
		}
		function CreateTag($file, $dir, $offset)
		{
			$tag = '<div class="col-md-3' . $offset . '" style="margin-top:5px;"><div class="panel panel-default"><div class="panel-heading"><label style="word-break:break-word" id=' . $file . 'Label>' . $file . '</label></div><a href="#" class="thumbnail" style="margin-bottom:0px;border:none" onclick="showImage(\'' . $dir . $file . '\')" data-toggle="modal" data-target="#imageModal"><img style="max-height:220px" src="' . $dir . $file . '"></a><div class="panel-footer"><label style="word-break:break-word">Path: ' . $dir . $file . '</label></br>Size: 1MB</br>Tags: mtg</br><button type="button" class="btn btn-primary btn-lg">Download</button></div></div></div>';
			return $tag;
		}
		
		function GetDirContents() {
			$dir = 'images/';
			$f1 = scandir($dir);
			$html = '<div class="row">';
			$index = 0;
			foreach($f1 as &$file) {
				if ($file !== '.' and $file !== '..') {
					if($index >= $start and $index < 6) {
						$offset = "";
						if($index == 0 || $index == 3)	{
							$offset = ' col-md-offset-1';
						}
						if($index == 3)
						{
							$html = $html . '</div><div class="row">';
						}
						$html = $html . CreateTag($file, $dir, $offset);
					}
					$index = $index + 1;
				}
			}
			return $html . '</div>';
		}
	?>
	<script>
		jQuery(document).ready(function(){
			$('#PButton').click(buttonClick);
		});
		function buttonClick() {
			var test = $("#defLabel");
			test.text('<?php echo btnC(); ?>');
		}
		function showImage(path) {
			$('#modalImage').attr("src", path);
			$('#imageModalLabel').html(path);
		}
	</script>
	<body>
		<nav class="navbar navbar-default" role="navigation">
			<div class="container-fluid">
				<div class="navbar-header">
				  <a class="navbar-brand" href="#">ImServ</a>
				</div>
			</div>
		</nav>
		<div class="container-fluid">
			<div class="row">
				<div class="col-md-4 col-md-offset-1">
					<button id=PButton type="button" class="btn btn-primary">Primary</button>
				</div>
			</div>
			<?php echo GetDirContents() ?>
		</div>
		<div class="modal fade" id="imageModal" tabindex="-1" role="dialog" aria-labelledby="imageModalLabel" aria-hidden="true">
		  <div class="modal-dialog">
			<div class="modal-content">
			  <div class="modal-header">
				<button type="button" class="close" data-dismiss="modal"><span aria-hidden="true">&times;</span><span class="sr-only">Close</span></button>
				<h4 class="modal-title" id="imageModalLabel" style="word-wrap:break-word;max-width:95%">Modal title</h4>
			  </div>
			  <div class="modal-body">
				<img class="img-responsive" id="modalImage" />
			  </div>
			</div>
		  </div>
		</div>
	</body>
</html>