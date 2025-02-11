<?php
// $Id$

function lab_migration_list_experiments()
{
  $user = \Drupal::currentUser();

  $proposal_data = lab_migration_get_proposa\Drupal\Core\Link;
  if (!$proposal_data) {
      RedirectResponse('');
      return;
  }

  $return_html = '<strong>Title of the Lab:</strong><br />' . $proposal_data->lab_title . '<br /><br />';
  $return_html .= '<strong>Proposer Name:</strong><br />' . $proposal_data->name_title . ' ' . $proposal_data->name . '<br /><br />';
  // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $return_html .= l('Upload Solution', 'lab-migration/code/upload') . '<br />';


  /* get experiment list */
  $experiment_rows = array();
  //$experiment_q = $injected_database->query("SELECT * FROM {lab_migration_experiment} WHERE proposal_id = %d ORDER BY number ASC", $proposal_data->id);
          	$query = \Drupal::database()->select('lab_migration_experiment');
							$query->fields('lab_migration_experiment');
							$query->condition('proposal_id', $proposal_data->id);
							$query->orderBy('number', 'ASC');
                     $experiment_q = $query->execute();

//var_dump($experiment_q->fetchObject());
//die;

  while ($experiment_data = $experiment_q->fetchObject())
  {


    $experiment_rows[] = array($experiment_data->number . ')&nbsp;&nbsp;&nbsp;&nbsp;' . $experiment_data->title, '', '', '');
    /* get solution list */
    //$solution_q = $injected_database->query("SELECT * FROM {lab_migration_solution} WHERE experiment_id = %d ORDER BY id ASC", $experiment_data->id);
    $query = \Drupal::database()->select('lab_migration_solution');
                $query->fields('lab_migration_solution');
                $query->condition('experiment_id', $experiment_data->id);
                $query->orderBy('id', 'ASC');
                $solution_q  = $query->execute();
    if ($solution_q) {
    	while ($solution_data = $solution_q->fetchObject()) {
    		$solution_status = '';
    		switch ($solution_data->approval_status) {
    		case 0: $solution_status = "Pending"; break;
    		case 1: $solution_status = "Approved"; break;
    		default: $solution_status = "Unknown"; break;
    		}
    		if ($solution_data->approval_status == 0) {
    			// @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $experiment_rows[] = array("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" . $solution_data->code_number . "   " . $solution_data->caption, '', $solution_status, l('Delete', 'lab-migration/code/delete/' . $solution_data->id));

    		} else {
    			$experiment_rows[] = array("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" . $solution_data->code_number . "   " . $solution_data->caption, '', $solution_status, '');
    		}
    		/* get solution files */
    		//$solution_files_q = $injected_database->query("SELECT * FROM {lab_migration_solution_files} WHERE solution_id = %d ORDER BY id ASC", $solution_data->id);
        $query = \Drupal::database()->select('lab_migration_solution_files');
                  $query->fields('lab_migration_solution_files');
                  $query->condition('solution_id', $solution_data->id);
                  $query->orderBy('id', 'ASC');
                  $solution_files_q = $query->execute();

    		if ($solution_files_q) {
    			while ($solution_files_data = $solution_files_q->fetchObject()) {
    				$code_file_type = '';
    				switch ($solution_files_data->filetype) {
    				case 'S': $code_file_type = 'Source'; break;
    				case 'R': $code_file_type = 'Result'; break;
    				case 'X': $code_file_type = 'Xcox'; break;
    				case 'U': $code_file_type = 'Unknown'; break;
    				default: $code_file_type = 'Unknown'; break;
    				}
    				// @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $experiment_rows[] = array("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" . l($solution_files_data->filename, 'lab-migration/download/file/' . $solution_files_data->id), $code_file_type, '', '');

    			}
    		}
				/* get dependencies files */
				//$dependency_q = $injected_database->query("SELECT * FROM {lab_migration_solution_dependency} WHERE solution_id = %d ORDER BY id ASC", $solution_data->id);
        $query = \Drupal::database()->select('lab_migration_solution_dependency');
                      $query->fields('lab_migration_solution_dependency');
                      $query->condition('solution_id', $solution_data->id);
                      $query->orderBy('id', 'ASC');
                      $dependency_q = $query->execute();
				while ($dependency_data = $dependency_q->fetchObject())
				{
					//$dependency_files_q = $injected_database->query("SELECT * FROM {lab_migration_dependency_files} WHERE id = %d", $dependency_data->dependency_id);
          $query = \Drupal::database()->select('lab_migration_dependency_files');
                      $query->fields('lab_migration_dependency_files');
                      $query->condition('id', $dependency_data->dependency_id);
                      $dependency_files_q = $query->execute();
					$dependency_files_data = $dependency_files_q->fetchObject();
					// @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $experiment_rows[] = array("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" . l($dependency_files_data->filename, 'lab-migration/download/dependency/' . $dependency_files_data->id), 'Dependency', '', '');

				}
    	}
    }
  }

  $experiment_header = array('No. Title of the Experiment', 'Type', 'Status', 'Actions');
 // $return_html .= theme_table($experiment_header, $experiment_rows);
 
 // @FIXME
// _theme has been renamed to __theme and should NEVER be called directly.
// Calling __theme directly can alter the expected output and potentially
// introduce security issues (see https://www.drupal.org/node/2195739). You
// should use renderable arrays instead.
// 
// 
// @see https://www.drupal.org/node/2195739
// $return_html .= theme('table', array('header' => $experiment_header, 'rows' => $experiment_rows));

  return $return_html;
}

function lab_migration_upload_code_form($form,$form_state)
{
 
  $user = \Drupal::currentUser();

  $proposal_data = lab_migration_get_proposa\Drupal\Core\Link;
  if (!$proposal_data) {
      RedirectResponse('');
      return;
  }

  /* add javascript for dependency selection effects */
  $dep_selection_js = "(function ($) {
  //alert('ok');
    $('#edit-existing-depfile-dep-lab-title').change(function() {
      var dep_selected = '';   
 
      /* showing and hiding relevant files */
     $('.form-checkboxes .option').hide();
      $('.form-checkboxes .option').each(function(index) {
        var activeClass = $('#edit-existing-depfile-dep-lab-title').va\Drupal\Core\Link;
        consloe.log(activeClass);
        if ($(this).children().hasClass(activeClass)) {
          $(this).show();
        }
        if ($(this).children().attr('checked') == true) {
          dep_selected += $(this).children().next().text() + '<br />';
        }
      });
      /* showing list of already existing dependencies */
      $('#existing_depfile_selected').html(dep_selected);
    });

    $('.form-checkboxes .option').change(function() {
      $('#edit-existing-depfile-dep-lab-title').trigger('change');
    });
    $('#edit-existing-depfile-dep-lab-title').trigger('change');
  }(jQuery));";
  // @FIXME
// The Assets API has totally changed. CSS, JavaScript, and libraries are now
// attached directly to render arrays using the #attached property.
// 
// 
// @see https://www.drupal.org/node/2169605
// @see https://www.drupal.org/node/2408597
// #attached($dep_selection_js, 'inline', 'header');


  $form['#attributes'] = array('enctype' => "multipart/form-data");

  $form['lab_title'] = array(
    '#type' => 'item',
    '#markup' => $proposal_data->lab_title,
    '#title' => t('Title of the Lab'),
  );
  $form['name'] = array(
    '#type' => 'item',
    '#markup' => $proposal_data->name_title . ' ' . $proposal_data->name,
    '#title' => t('Proposer Name'),
  );

  /* get experiment list */
  $experiment_rows = array();
  //$experiment_q = $injected_database->query("SELECT * FROM {lab_migration_experiment} WHERE proposal_id = %d ORDER BY id ASC", $proposal_data->id);
  $query = \Drupal::database()->select('lab_migration_experiment');
                $query->fields('lab_migration_experiment');
                $query->condition('proposal_id', $proposal_data->id);
                $query->orderBy('id', 'ASC');
                $experiment_q = $query->execute();
  while ($experiment_data = $experiment_q->fetchObject())
  {
    $experiment_rows[$experiment_data->id] = $experiment_data->number . '. ' . $experiment_data->title;
  }
  $form['experiment'] = array(
    '#type' => 'select',
    '#title' => t('Title of the Experiment'),
    '#options' => $experiment_rows,
    '#multiple' => FALSE,
    '#size' => 1,
    '#required' => TRUE,
  );

  $form['code_number'] = array(
    '#type' => 'textfield',
    '#title' => t('Code No'),
    '#size' => 5,
    '#maxlength' => 10,
    '#description' => t(""),
    '#required' => TRUE,
  );
  $form['code_caption'] = array(
    '#type' => 'textfield',
    '#title' => t('Caption'),
    '#size' => 40,
    '#maxlength' => 255,
    '#description' => t(''),
    '#required' => TRUE,
  );
  $form['os_used'] = array(
    '#type' => 'select',
    '#title' => t('Operating System used'),
    '#options' => array(
      'Linux' => 'Linux',
      'Windows' => 'Windows',
      'Mac' => 'Mac'
    ),
    '#required' => TRUE,
  );
  $form['r_version'] = array(
    '#type' => 'select',
    '#title' => t('R version used'),
    '#options' => _lm_list_of_software_version(),
    '#required' => TRUE,
  );
  $form['toolbox_used'] = array(
    '#type' => 'hidden',
    '#title' => t('Toolbox used (If any)'),
'#default_value'=>'none',
  );
  $form['code_warning'] = array(
    '#type' => 'item',
    '#title' => t('Upload all the r project files in .zip format'),
    '#prefix' => '<div style="color:red">',
    '#suffix' => '</div>',
  );
  $form['sourcefile'] = array(
    '#type' => 'fieldset',
    '#title' => t('Main or Source Files'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['sourcefile']['sourcefile1'] = array(
      '#type' => 'file',
      '#title' => t('Upload main or source file'),
      '#size' => 48,
      '#description' => t('Only alphabets and numbers are allowed as a valid filename.') . '<br />' .
      t('Allowed file extensions: ') . \Drupal::config('lab_migration.settings')->get('lab_migration_source_extensions'),
  );

 /* $form['dep_files'] = array(
    '#type' => 'item',
    '#title' => t('Dependency Files'),
  );*/

  /************ START OF EXISTING DEPENDENCIES **************/

  /* existing dependencies */
 /* $form['existing_depfile'] = array(
    '#type' => 'fieldset',
    '#title' => t('Use Already Existing Dependency Files'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#prefix' => '<div id="existing-depfile-wrapper">',
    '#suffix' => '</div>',
    '#tree' => TRUE,
  );

  /* existing dependencies */
/* $form['existing_depfile']['selected'] = array(
    '#type' => 'item',
    '#title' => t('Existing Dependency Files Selected'),
    '#markup' => '<div id="existing_depfile_selected"></div>',
  );

/*  $form['existing_depfile']['dep_lab_title'] = array(
      '#type' => 'select',
      '#title' => t('Title of the Lab'),
      '#options' => _list_of_lab_titles(),
  );
*/
  /*list($files_options, $files_options_class) = _list_of_dependency_files();
  $form['existing_depfile']['dep_experiment_files'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Dependency Files'),
      '#options' => $files_options,
      '#options_class' => $files_options_class,
      '#multiple' => TRUE,
  );
   

  $form['existing_depfile']['dep_upload'] = array(
      '#type' => 'item',
      '#markup' => l('Upload New Depedency Files', 'lab-migration/code/upload_dep'),
  );
  /************ END OF EXISTING DEPENDENCIES **************/

  /*$form['result'] = array(
    '#type' => 'fieldset',
    '#title' => t('Result Files'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['result']['result1'] = array(
      '#type' => 'file',
      '#title' => t('Upload result file'),
      '#size' => 48,
      '#description' => t('Separate filenames with underscore. No spaces or any special characters allowed in filename.') . '<br />' .
      t('Allowed file extensions: ') . $config->get('lab_migration_result_extensions', ''),
  );
  $form['result']['result2'] = array(
      '#type' => 'file',
      '#title' => t('Upload result file'),
      '#size' => 48,
      '#description' => t('Separate filenames with underscore. No spaces or any special characters allowed in filename.') . '<br />' .
      t('Allowed file extensions: ') . $config->get('lab_migration_result_extensions', ''),
  );

  $form['xcos'] = array(
    '#type' => 'fieldset',
    '#title' => t('XCOS Files'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['xcos']['xcos1'] = array(
      '#type' => 'file',
      '#title' => t('Upload xcos file'),
      '#size' => 48,
      '#description' => t('Separate filenames with underscore. No spaces or any special characters allowed in filename.') . '<br />' .
      t('Allowed file extensions: ') . $config->get('lab_migration_xcos_extensions', ''),
  );
  $form['xcos']['xcos2'] = array(
      '#type' => 'file',
      '#title' => t('Upload xcos file'),
      '#size' => 48,
      '#description' => t('Separate filenames with underscore. No spaces or any special characters allowed in filename.') . '<br />' .
      t('Allowed file extensions: ') . $config->get('lab_migration_xcos_extensions', ''),
  );
*/
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit')
  );

  // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $form['cancel'] = array(
//     '#type' => 'markup',
//     '#value' => l(t('Cancel'), 'lab-migration/code'),
//   );

  return $form;
}

function lab_migration_upload_code_form_validate($form, &$form_state)
{
  if (!lab_migration_check_code_number($form_state['values']['code_number']))
    $form_state->setErrorByName('code_number', t('Invalid Code Number. Code Number can contain only numbers.'));

  if (!lab_migration_check_name($form_state['values']['code_caption']))
    $form_state->setErrorByName('code_caption', t('Caption can contain only alphabets, numbers and spaces.'));

  if(!$form_state['values']['os_used'])
    $form_state->setErrorByName('os_used', t('Please select the operating system used.'));

  if(!$form_state['values']['r_version'])
    $form_state->setErrorByName('r_version', t('Please select the R version used.'));

  if (isset($_FILES['files']))
  {
    /* check if atleast one source or result file is uploaded */  
    if ( ! ($_FILES['files']['name']['sourcefile1'] ))
      $form_state->setErrorByName('sourcefile1', t('Please upload atleast one main or source file.'));

    /* check for valid filename extensions */  
    foreach ($_FILES['files']['name'] as $file_form_name => $file_name)
    {
      if ($file_name)
      {
        /* checking file type */
        if (strstr($file_form_name, 'source'))
          $file_type = 'S';
        else if (strstr($file_form_name, 'result'))
          $file_type = 'R';
        else if (strstr($file_form_name, 'xcos'))
          $file_type = 'X';
        else
          $file_type = 'U';

        $allowed_extensions_str = '';
        switch ($file_type)
        {
        case 'S':
          $allowed_extensions_str = \Drupal::config('lab_migration.settings')->get('lab_migration_source_extensions');
          break;
        case 'R':
          $allowed_extensions_str = \Drupal::config('lab_migration.settings')->get('lab_migration_result_extensions');
          break;
        case 'X':
          $allowed_extensions_str = \Drupal::config('lab_migration.settings')->get('lab_migration_xcos_extensions');
          break;
        }
        $allowed_extensions = explode(',' , $allowed_extensions_str);
        $tmp_ext = explode('.', strtolower($_FILES['files']['name'][$file_form_name]));
        $temp_extension = end($tmp_ext);
        if (!in_array($temp_extension, $allowed_extensions))
          $form_state->setErrorByName($file_form_name, t('Only file with ' . $allowed_extensions_str . ' extensions can be uploaded.'));
        if ($_FILES['files']['size'][$file_form_name] <= 0)
          $form_state->setErrorByName($file_form_name, t('File size cannot be zero.'));

        /* check if valid file name */
        if (!lab_migration_check_valid_filename($_FILES['files']['name'][$file_form_name]))
         $form_state->setErrorByName($file_form_name, t('Invalid file name specified. Only alphabets and numbers are allowed as a valid filename.'));
      }
    }
  }

  /* add javascript dependency selection effects */
 $dep_selection_js = " (function ($) {
 
    $('#edit-existing-depfile-dep-lab-title').change(function() {
    console.log('ok');
      var dep_selected = ''; 
      /* showing and hiding relevant files */
    $('.form-checkboxes .option').hide();
      
      $('.form-checkboxes .option').each(function(index) {
        var activeClass = $('#edit-existing-depfile-dep-lab-title').va\Drupal\Core\Link;
        if ($(this).children().hasClass(activeClass)) {
          $(this).show();
        }
        if ($(this).children().attr('checked') == true) {
          dep_selected += $(this).children().next().text() + '<br />';
        }
      });
      /* showing list of already existing dependencies */
     $('#existing_depfile_selected').html(dep_selected);
    });

    $('.form-checkboxes .option').change(function() {
      $('#edit-existing-depfile-dep-lab-title').trigger('change');
    });
    $('#edit-existing-depfile-dep-lab-title').trigger('change');
  })(jQuery);";
// @FIXME
// The Assets API has totally changed. CSS, JavaScript, and libraries are now
// attached directly to render arrays using the #attached property.
// 
// 
// @see https://www.drupal.org/node/2169605
// @see https://www.drupal.org/node/2408597
// #attached($dep_selection_js, 'inline', 'header');

 
  // #attached('jQuery(document).ready(function () { alert("Hello!"); });', 'inline');
 // drupal_static_reset('#attached') ;
}

function lab_migration_upload_code_form_submit($form, &$form_state) {
  $user = \Drupal::currentUser();

  $root_path = lab_migration_path();

  $proposal_data = lab_migration_get_proposa\Drupal\Core\Link;
  if (!$proposal_data) {
      RedirectResponse('');
      return;
  }

  $proposal_id = $proposal_data->id;
  $proposal_drectory = $proposal_data->directory_name;

  /************************ check experiment details ************************/
  $experiment_id = (int)$form_state['values']['experiment'];
  //$experiment_q = $injected_database->query("SELECT * FROM {lab_migration_experiment} WHERE id = %d AND proposal_id = %d LIMIT 1", $experiment_id, $proposal_id);
  $query = \Drupal::database()->select('lab_migration_experiment');
              $query->fields('lab_migration_experiment');
              $query->condition('id', $experiment_id);
              $query->condition('proposal_id', $proposal_id);
              $query->range(0, 1);
              $experiment_q = $query->execute();
  $experiment_data = $experiment_q->fetchObject();
  if (!$experiment_data)
  {
    \Drupal::messenger()->addError("Invalid experiment seleted");
    RedirectResponse('lab-migration/code');
  }

  /* create proposal folder if not present */
  $dest_path = $proposal_drectory . '/';
  if (!is_dir($root_path . $dest_path))
    mkdir($root_path . $dest_path);

  /*  get solution details - dont allow if already solution present */
  $code_number = $experiment_data->number . '.' . $form_state['values']['code_number'];

  //$cur_solution_q = $injected_database->query("SELECT * FROM {lab_migration_solution} WHERE experiment_id = %d AND code_number = '%s'", $experiment_id, $experiment_data->number . '.' . $form_state['values']['code_number']);
  $query = \Drupal::database()->select('lab_migration_solution');
              $query->fields('lab_migration_solution');
              $query->condition('experiment_id', $experiment_id);
              $query->condition('code_number', $code_number);
              $cur_solution_q = $query->execute();
  if ($cur_solution_d = $cur_solution_q->fetchObject())
  {
    if ($cur_solution_d->approval_status == 1)
    {
      \Drupal::messenger()->addError(t("Solution already approved. Cannot overwrite it."));
      RedirectResponse('lab-migration/code');
      return;
    } else if ($cur_solution_d->approval_status == 0) {
      \Drupal::messenger()->addError(t("Solution is under pending review. Delete the solution and reupload it."));
      RedirectResponse('lab-migration/code');
      return;
    } else {
      \Drupal::messenger()->addError(t("Error uploading solution. Please contact administrator."));
      RedirectResponse('lab-migration/code');
      return;
    }
  }

  /* creating experiment directories */
  $dest_path .= 'EXP' . $experiment_data->number . '/';
  if (!is_dir($root_path . $dest_path))
    mkdir($root_path . $dest_path);

  /* creating code directories */
  $dest_path .= 'CODE' . $experiment_data->number . '.' . $form_state['values']['code_number'] . '/';
  if (!is_dir($root_path . $dest_path))
    mkdir($root_path . $dest_path);
 /* creating file path */
 $file_path = 'EXP' . $experiment_data->number . '/' . 'CODE' . $experiment_data->number . '.' . $form_state['values']['code_number'] . '/';
  /* creating solution database entry */
  $query = "INSERT INTO {lab_migration_solution} (experiment_id, approver_uid, code_number, caption, approval_date, approval_status, timestamp, os_used, r_version, toolbox_used) VALUES (:experiment_id, :approver_uid, :code_number, :caption, :approval_date, :approval_status, :timestamp, :os_used, :r_version, :toolbox_used)";
    $args = array(
                    ":experiment_id" => $experiment_id,
                    ":approver_uid" => 0,
                    ":code_number" => $experiment_data->number . '.' . $form_state['values']['code_number'],
                    ":caption" => $form_state['values']['code_caption'],
                    ":approval_date" => 0,
                    ":approval_status" => 0,
                    ":timestamp" => time(),
                    ":os_used" => $form_state['values']['os_used'],
                    ":r_version" => $form_state['values']['r_version'],
                    ":toolbox_used" => $form_state['values']['toolbox_used']
            );
  $solution_id = \Drupal::database()->query($query, $args, $query);
//var_dump('solution id= '.$solution_id.  '&&& dep file = '.array_filter($form_state['values']['existing_depfile']['dep_experiment_files']));

//die;
  /* linking existing dependencies */
 /* foreach ($form_state['values']['existing_depfile']['dep_experiment_files'] as $row)
  {
    if ($row > 0)
    {*/
      /* insterting into database */
     /* $query = "INSERT INTO {lab_migration_solution_dependency} (solution_id, dependency_id)
        VALUES (:solution_id, :dependency_id)";
      $args = array(
                    ":solution_id" => $solution_id,
                    ":dependency_id" => $row
               );  
      $injected_database->query( $query,$args);
    }
  }*/

  /* uploading files */
  foreach ($_FILES['files']['name'] as $file_form_name => $file_name)
  {
    if ($file_name)
    {
      /* checking file type */
      if (strstr($file_form_name, 'source'))
        $file_type = 'S';
      else if (strstr($file_form_name, 'result'))
        $file_type = 'R';
      else if (strstr($file_form_name, 'xcos'))
        $file_type = 'X';
      else
        $file_type = 'U';

      if (file_exists($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]))
      {
        \Drupal::messenger()->addError(t("Error uploading file. File !filename already exists.", array('!filename' => $_FILES['files']['name'][$file_form_name])));
        return;
      }

      /* uploading file */
      if (move_uploaded_file($_FILES['files']['tmp_name'][$file_form_name], $root_path . $dest_path . $_FILES['files']['name'][$file_form_name]))
      {
        /* for uploaded files making an entry in the database */
        $query = "INSERT INTO {lab_migration_solution_files} (solution_id, filename, filepath, filemime, filesize, filetype, timestamp)
          VALUES (:solution_id, :filename, :filepath, :filemime, :filesize, :filetype, :timestamp)";
          $args = array(
                    ":solution_id" => $solution_id,
                    ":filename" => $_FILES['files']['name'][$file_form_name],
                    ":filepath" => $file_path . $_FILES['files']['name'][$file_form_name],
                    ":filemime" => mime_content_type($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]),
                    ":filesize" => $_FILES['files']['size'][$file_form_name],
                    ":filetype" => $file_type,
                    ":timestamp" => time()
                 );
        \Drupal::database()->query($query, $args);
        \Drupal::messenger()->addStatus($file_name . ' uploaded successfully.');
      } else {
        \Drupal::messenger()->addError('Error uploading file: ' . $dest_path . $file_name);
      }
    }
  }
  \Drupal::messenger()->addStatus('Solution uploaded successfully.');

 /* sending email */
  $email_to = $user->mail;

  $from = \Drupal::config('lab_migration.settings')->get('lab_migration_from_email');
  $bcc= \Drupal::config('lab_migration.settings')->get('lab_migration_emails');
  $cc=\Drupal::config('lab_migration.settings')->get('lab_migration_cc_emails');  
  $param['solution_uploaded']['solution_id'] = $solution_id;
  $param['solution_uploaded']['user_id'] = $user->uid;
  $param['solution_uploaded']['headers']=array('From'=>$from,'MIME-Version'=> '1.0',
    			'Content-Type'=> 'text/plain; charset=UTF-8; format=flowed; delsp=yes',
    			'Content-Transfer-Encoding' => '8Bit',
    			'X-Mailer'=> 'Drupal','Cc' => $cc, 'Bcc' => $bcc);

  if (!drupal_mail('lab_migration', 'solution_uploaded', $email_to, language_default(), $param, $from, TRUE))
    \Drupal::messenger()->addError('Error sending email message.');

  RedirectResponse('lab-migration/code');
}

/******************************************************************************/
/************************** GENERAL FUNCTIONS *********************************/
/******************************************************************************/

function _list_of_lab_titles()
{
  $lab_titles = array('0' => 'Please select...');
  //$lab_titles_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE approval_status = 1 OR approval_status = 3 ORDER BY lab_title ASC");
  $query = \Drupal::database()->select('lab_migration_proposal');
              $query->fields('lab_migration_proposal');

              $or = db_or();
              $or->condition('approval_status', 1);
              $or->condition('approval_status', 3);
              $query->condition($or);
              $query->orderBy('lab_title', 'ASC');
              $lab_titles_q = $query->execute();

  while ($lab_titles_data = $lab_titles_q->fetchObject())
  {
    $lab_titles[$lab_titles_data->id] = $lab_titles_data->lab_title . ' (Proposed by ' . $lab_titles_data->name . ')';
  }
  return $lab_titles;
}

function _list_of_dependency_files()
{
//  $dependancy_proposal_id = $form_state['values']['existing_depfile']['dep_lab_title'];
//var_dump($dependancy_proposal_id);
  $dependency_files = array();
  $dependency_files_class = array();
  //$dependency_files_q = $injected_database->query("SELECT * FROM {lab_migration_dependency_files} WHERE proposal_id = %d ORDER BY filename ASC", $dependancy_proposal_id);
  $query = \Drupal::database()->select('lab_migration_dependency_files');
              $query->fields('lab_migration_dependency_files');
              $query->orderBy('filename', 'ASC');
            //  $query->condition('proposal_id',$dependancy_proposal_id);
              $dependency_files_q = $query->execute();

  while ($dependency_files_data = $dependency_files_q->fetchObject())
  {
    $temp_caption = '';
    if ($dependency_files_data->caption)
      $temp_caption .= ' (' . $dependency_files_data->caption . ')';
    // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $dependency_files[$dependency_files_data->id] = l($dependency_files_data->filename . $temp_caption, 'lab-migration/download/dependency/' . $dependency_files_data->id, array('attributes' => array('class' => $dependency_files_data->proposal_id)));

    $dependency_files_class[$dependency_files_data->id] = $dependency_files_data->proposal_id;
    $dependency_files_value[$dependency_files_data->id] = $dependency_files_data->proposal_id;
  }
  return array($dependency_files, $dependency_files_class,  $dependency_files_value);
}