<?php
// $Id$
function lab_migration_upload_dependency_form($form, $form_state)
  {
    $user = \Drupal::currentUser();
    $proposal_data = lab_migration_get_proposa\Drupal\Core\Link;
    if (!$proposal_data)
      {
        RedirectResponse('');
        return;
      }
    $form['#attributes'] = array(
        'enctype' => "multipart/form-data"
    );
    $form['lab_title'] = array(
        '#type' => 'item',
        '#value' => $proposal_data->lab_title,
        '#title' => t('Title of the Lab')
    );
    $form['name'] = array(
        '#type' => 'item',
        '#value' => $proposal_data->name_title . ' ' . $proposal_data->name,
        '#title' => t('Proposer Name')
    );
    $form['existing_depfile'] = array(
        '#type' => 'item',
        '#value' => _list_existing_dependency($proposal_data->id),
        '#title' => t('List of existing dependency files for this book')
    );
    $form['depfile'] = array(
        '#type' => 'fieldset',
        '#title' => t('Upload Dependency Files'),
        '#collapsible' => FALSE,
        '#collapsed' => FALSE
    );
    $form['depfile']['depfile1'] = array(
        '#type' => 'file',
        '#title' => t('Upload dependency file'),
        '#description' => t("Allowed file extensions : ") . \Drupal::config('lab_migration.settings')->get('lab_migration_dependency_extensions')
    );
    $form['depfile']['depfile1_caption'] = array(
        '#type' => 'textfield',
        '#title' => t('Caption for dependency file'),
        '#size' => 15,
        '#maxlength' => 100,
        '#required' => TRUE
    );
    $form['depfile']['depfile1_description'] = array(
        '#type' => 'textarea',
        '#title' => t('Brief Description of the dependency file')
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit')
    );
    // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $form['cancel'] = array(
//         '#type' => 'markup',
//         '#value' => l(t('Back'), 'lab_migration/code')
//     );

    return $form;
  }
function lab_migration_upload_dependency_form_validate($form, &$form_state)
  {
    $user = \Drupal::currentUser();
    /* get approved proposal details */
    //$proposal_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE uid = %d OR solution_provider_uid = %d ORDER BY id DESC LIMIT 1", $user->uid, $user->uid);
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $or = db_or();
    $or->condition('uid', $user->uid);
    $or->condition('solution_provider_uid', $user->uid);
    $query->condition($or);
    $query->orderBy('id', 'DESC');
    $query->range(0, 1);
    $proposal_q = $query->execute();
    $proposal_data = $proposal_q->fetchObject();
    if (!$proposal_data)
      {
        $form_state->setErrorByName('', t('Invalid1'));
      }
    if (!lab_migration_check_name($form_state['values']['depfile1_caption']))
        $form_state->setErrorByName('code_caption', t('Caption can contain only alphabets, numbers and spaces.'));
    if (isset($_FILES['files']))
      {
        /* check for valid filename extensions */
        $allowed_extensions = explode(',', \Drupal::config('lab_migration.settings')->get('lab_migration_dependency_extensions'));
        foreach ($_FILES['files']['name'] as $file_form_name => $file_name)
          {
            if ($file_name)
              {
                $temp_extension = end(explode('.', strtolower($_FILES['files']['name'][$file_form_name])));
                if (!in_array($temp_extension, $allowed_extensions))
                    $form_state->setErrorByName($file_form_name, t('Only ' . \Drupal::config('lab_migration.settings')->get('lab_migration_dependency_extensions') . ' extensions can be uploaded.'));
                if ($_FILES['files']['size'][$file_form_name] <= 0)
                    $form_state->setErrorByName($file_form_name, t('File size cannot be zero.'));
                /* check if file already exists */
                //$dep_exists_data = ($injected_database->query("SELECT * FROM {lab_migration_dependency_files} WHERE filename = '%s'", $_FILES['files']['name'][$file_form_name]))->fetchObject();
                $query = \Drupal::database()->select('lab_migration_dependency_files');
                $query->fields('lab_migration_dependency_files');
                $query->condition('filename', $_FILES['files']['name'][$file_form_name]);
                $dep_exists_data = $query->execute();
                if ($dep_exists_data)
                    $form_state->setErrorByName($file_form_name, t('Dependency file with the same name has already been uploaded in this or some other lab solution. Please rename the file and try again.'));
                /* check if valid file name */
                if (!lab_migration_check_valid_filename($_FILES['files']['name'][$file_form_name]))
                    $form_state->setErrorByName($file_form_name, t('Invalid file name specified. Only alphabets, numbers and underscore is allowed as a valid filename.'));
              }
          }
      }
  }
function lab_migration_upload_dependency_form_submit($form, &$form_state)
  {
    $user = \Drupal::currentUser();
    $root_path = lab_migration_path();
    $proposal_data = lab_migration_get_proposa\Drupal\Core\Link;
    if (!$proposal_data)
      {
        RedirectResponse('');
        return;
      }
    $dest_path .= 'DEPENDENCIES' . '/';
    if (!is_dir($root_path . $dest_path))
        mkdir($root_path . $dest_path);
    /* uploading dependencies */
    $file_upload_counter = 0;
    $dependency_ids = array();
    $dependency_names = array();
    foreach ($_FILES['files']['name'] as $file_form_name => $file_name)
      {
        if ($file_name)
          {
            /* uploading file */
            if (move_uploaded_file($_FILES['files']['tmp_name'][$file_form_name], $root_path . $dest_path . $_FILES['files']['name'][$file_form_name]))
              {
                /* for uploaded files making an entry in the database */
                $query = "INSERT INTO {lab_migration_dependency_files} (proposal_id, filename, filepath, filemime, filesize, caption, description, timestamp)
          VALUES (:proposal_id, :filename, :filepath, :filemime, :filesize, :caption, :description, :timestamp)";
                $args = array(
                    ":proposal_id" => $proposal_data->id,
                    ":filename" => $_FILES['files']['name'][$file_form_name],
                    ":filepath" => $dest_path . $_FILES['files']['name'][$file_form_name],
                    ":filemime" => $_FILES['files']['type'][$file_form_name],
                    ":filesize" => $_FILES['files']['size'][$file_form_name],
                    ":caption" => \Drupal\Component\Utility\Html::escape($form_state['values'][$file_form_name . '_caption']),
                    ":description" => \Drupal\Component\Utility\Html::escape($form_state['values'][$file_form_name . '_description']),
                    ":timestamp" => time()
                );
                $dependency_ids[] = \Drupal::database()->query($query, $args, $query);
                \Drupal::messenger()->addStatus($file_name . ' uploaded successfully.');
                $dependency_names[] = $_FILES['files']['name'][$file_form_name];
                $file_upload_counter++;
              }
            else
              {
                \Drupal::messenger()->addError('Error uploading dependency : ' . $dest_path . $_FILES['files']['name'][$file_form_name]);
              }
          }
      }
    if ($file_upload_counter > 0)
      {
        \Drupal::messenger()->addStatus('Dependencies uploaded successfully.');
        /* sending email */
        $param['dependency_uploaded']['user_id'] = $user->uid;
        $param['dependency_uploaded']['dependency_names'] = $dependency_names;
        $email_to = $user->mail . ', ' . \Drupal::config('lab_migration.settings')->get('lab_migration_emails');
        if (!drupal_mail('lab_migration', 'dependency_uploaded', $email_to, language_default(), $param, \Drupal::config('lab_migration.settings')->get('lab_migration_from_email'), TRUE))
            \Drupal::messenger()->addError('Error sending email message.');
      }
    RedirectResponse('lab-migration/code/upload-dep');
  }
function _list_existing_dependency($proposal_id)
  {
    $return_html = '<ul>';
    // $proposal_dependency_files_q = $injected_database->query("SELECT * FROM {lab_migration_dependency_files} WHERE proposal_id = %d ORDER BY filename ASC", $proposal_id);
    $query = \Drupal::database()->select('lab_migration_dependency_files');
    $query->fields('lab_migration_dependency_files');
    $query->condition('proposal_id', $proposal_id);
    $query->orderBy('filename', 'ASC');
    $proposal_dependency_files_q = $query->execute();
    $counter = 0;
    while ($proposal_dependency_files_data = $proposal_dependency_files_q->fetchObject())
      {
        $temp_caption = '';
        if ($proposal_dependency_files_data->caption)
            $temp_caption = ' (' . $proposal_dependency_files_data->caption . ')';
        // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $return_html .= '<li>' . l($proposal_dependency_files_data->filename . $temp_caption, 'lab-migration/download/dependency/' . $proposal_dependency_files_data->id) . '</li>';

        $counter++;
      }
    if ($counter == 0)
        $return_html .= '<li>(None)</li>';
    $return_html .= '</ul>';
    return $return_html;
  }
