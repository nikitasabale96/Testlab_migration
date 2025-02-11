<?php
// $Id$
/*
Approval Status :
0 - Pending
1 - Approved
2 - Dis-Approved
3 - Solved
Solution Status :
0 - Pending
1 - Approved
2 - Dis-Approved
Solution Display :
0 - No
1 - Yes

Tables :
lab_migration_solution : approval_status
0 - Pending
1 - Approved
2 - Disapproved (delete it)
*/
function lab_migration_proposal_form($form, &$form_state)
  {
    $user = \Drupal::currentUser();
    $form = array();
    $state =  _lab_migration_list_of_states();
    $selected_state = isset($form_state['values']['all_state'])?$form_state['values']['all_state']:key($state);
    $district = _lab_migration_list_of_district();
    $selected_district = isset($form_state['values']['district'])?$form_state['values']['district']:key($district);
    $city = _lab_migration_list_of_cities();
    $selected_city = isset($form_state['values']['city'])?$form_state['values']['city']:key($city);
    $pincode = _lab_migration_list_of_city_pincode();
    $selected_pincode = isset($form_state['values']['picode'])?$form_state['values']['pincode']:key($pincode);
    /************************ start approve book details ************************/
    if ($user->uid == 0) {
        $msg =  \Drupal::messenger()->addError(t('It is mandatory to ' . \Drupal\Core\Link::fromTextAndUrl('login', \Drupal\Core\Url::fromRoute('user.page')) . ' on this website to access the lab proposal form. If you are new user please create a new account first.'));
         //RedirectResponse('lab-migration-project');
         RedirectResponse('user');
         return $msg;
    }
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('uid', $user->uid);
    $query->orderBy('id', 'DESC');
    $query->range(0, 1);
    $proposal_q = $query->execute();
    $proposal_data = $proposal_q->fetchObject();
    if ($proposal_data)
      {
        if ($proposal_data->approval_status == 0 || $proposal_data->approval_status == 1)
          {
            \Drupal::messenger()->addStatus(t('We have already received your proposal.'));
            RedirectResponse('');
            return;
          }
      }
    $form['#attributes'] = array(
        'enctype' => "multipart/form-data"
    );
    $form['name_title'] = array(
        '#type' => 'select',
        '#title' => t('Title'),
        '#options' => array(
            'Dr' => 'Dr',
            'Prof' => 'Prof'
        ),
        '#required' => TRUE
    );
    $form['name'] = array(
        '#type' => 'textfield',
        '#title' => t('Name of the Proposer'),
        '#size' => 200,
        '#attributes' => array(
            'placeholder' => t('Enter your full name')
        ),
        '#maxlength' => 200,
        '#required' => TRUE
    );
    $form['email_id'] = array(
        '#type' => 'textfield',
        '#title' => t('Email'),
        '#size' => 30,
        '#value' => $user->mail,
        '#disabled' => TRUE
    );
    $form['contact_ph'] = array(
        '#type' => 'textfield',
        '#title' => t('Contact No.'),
        '#size' => 30,
        '#attributes' => array(
            'placeholder' => t('Enter your contact number')
        ),
        '#maxlength' => 15,
        '#required' => TRUE
    );
    $form['department'] = array(
        '#type' => 'select',
        '#title' => t('Department/Branch'),
        '#options' => _lm_list_of_departments(),
        '#required' => TRUE
    );
    $form['university'] = array(
        '#type' => 'textfield',
        '#title' => t('University/ Institute'),
        '#size' => 80,
        '#maxlength' => 200,
        '#required' => TRUE,
        '#attributes' => array(
            'placeholder' => 'Insert full name of your institute/ university.... '
        )
    );
   $form['country'] = array(
        '#type' => 'select',
        '#title' => t('Country'),
        '#options' => array(
            'India' => 'India',
            'Others' => 'Others'
        ),
        '#required' => TRUE,
        '#tree' => TRUE,
        '#validated' => TRUE
    );
    $form['other_country'] = array(
        '#type' => 'textfield',
        '#title' => t('Other than India'),
        '#size' => 100,
        '#attributes' => array(
            'placeholder' => t('Enter your country name')
        ),
        '#states' => array(
            'visible' => array(
                ':input[name="country"]' => array(
                    'value' => 'Others'
                )
            )
        )
    );
    $form['other_state'] = array(
        '#type' => 'textfield',
        '#title' => t('State other than India'),
        '#size' => 100,
        '#attributes' => array(
            'placeholder' => t('Enter your state/region name')
        ),
        '#states' => array(
            'visible' => array(
                ':input[name="country"]' => array(
                    'value' => 'Others'
                )
            )
        )
    );
    $form['other_city'] = array(
        '#type' => 'textfield',
        '#title' => t('City other than India'),
        '#size' => 100,
        '#attributes' => array(
            'placeholder' => t('Enter your city name')
        ),
        '#states' => array(
            'visible' => array(
                ':input[name="country"]' => array(
                    'value' => 'Others'
                )
            )
        )
    );
    $form['all_state'] = array(
        '#type' => 'select',
        '#title' => t('State'),
        '#options' => _lm_list_of_states(),
        '#validated' => TRUE,
        '#states' => array(
            'visible' => array(
                ':input[name="country"]' => array(
                    'value' => 'India'
                )
            )
        )
    );
    $form['city'] = array(
        '#type' => 'select',
        '#title' => t('City'),
        '#options' => _lm_list_of_cities(),
        '#states' => array(
            'visible' => array(
                ':input[name="country"]' => array(
                    'value' => 'India'
                )
            )
        )
    );
    $form['pincode'] = array(
        '#type' => 'textfield',
        '#title' => t('Pincode'),
        '#size' => 30,
        '#maxlength' => 6,
        '#required' => TRUE,
        '#attributes' => array(
            'placeholder' => 'Enter pincode....'
        )
    );
    /***************************************************************************/
    $form['hr'] = array(
        '#type' => 'item',
        '#markup' => '<hr>'
    );
    $form['operating_system'] = array(
        '#type' => 'textfield',
        '#title' => t('Operating System'),
        '#size' => 30,
        '#maxlength' => 100,
        '#required' => TRUE
    );
    $form['version'] = array(
        '#type' => 'select',
        '#title' => t('R Version'),
        '#options' => _lm_list_of_software_version(),
        '#required' => TRUE
    );
    $form['older'] = array(
        '#type' => 'textfield',
        '#size' => 30,
        '#maxlength' => 50,
        //'#required' => TRUE,
        '#description' => t('Specify the Older version used'),
        '#states' => array(
            'visible' => array(
                ':input[name="version"]' => array(
                    'value' => 'Others'
                )
            )
        )
    );
    $form['syllabus_link'] = array(
        '#type' => 'textfield',
        '#title' => t('Syllabus Link'),
        '#required' => TRUE,
        '#attributes' => array(
            'placeholder' => 'Add the syllabus link '
        )
    );
    $form['syllabus_copy'] = array(
        '#type' => 'fieldset',
        '#title' => t('<span class="form-required form-item" title="This field is required.">Syllabus copy (PDF) Files *</span>'),
        '#collapsible' => FALSE,
        '#collapsed' => FALSE
    );
    $form['syllabus_copy']['syllabus_copy_file'] = array(
        '#type' => 'file',
        '#title' => t('Upload pdf file'),
        '#size' => 48,
        '#description' => t('Separate filenames with underscore. No spaces or any special characters allowed in filename.') .
                '<br />' . t('<span style="color:red;">Allowed file extensions : ') .
                            \Drupal::config('lab_migration.settings')->get('lab_migration_syllabus_file_extensions') . '</span>'
    );

    $form['lab_title'] = array(
        '#type' => 'textfield',
        '#title' => t('Title of the Lab'),
        '#size' => 100,
        '#required' => TRUE
    );
    $first_experiemnt = TRUE;
    for ($counter = 1; $counter <= 15; $counter++)
      {
        if ($counter <= 5)
          {
            $form['lab_experiment-' . $counter] = array(
                '#type' => 'textfield',
                '#title' => t('Title of the Experiment ') . $counter,
                '#size' => 100,
                '#required' => TRUE
            );
            $namefield = "lab_experiment-" . $counter;
            $form['lab_experiment_description-' . $counter] = array(
                '#type' => 'textarea',
                '#required' => TRUE,
                '#attributes' => array(
                    'placeholder' => t('Enter Description for your experiment ' . $counter),
                    'cols' => 50,
                    'rows' => 4
                ),
                '#title' => t('Description for Experiment ') . $counter,
                '#states' => array(
                    'invisible' => array(
                        ':input[name=' . $namefield . ']' => array(
                            'value' => ""
                        )
                    )
                )
            );
          }
        else
          {
            $form['lab_experiment-' . $counter] = array(
                '#type' => 'textfield',
                '#title' => t('Title of the Experiment ') . $counter,
                '#size' => 100,
                '#required' => FALSE
            );
            $namefield = "lab_experiment-" . $counter;
            $form['lab_experiment_description-' . $counter] = array(
                '#type' => 'textarea',
                '#required' => FALSE,
                '#attributes' => array(
                    'placeholder' => t('Enter Description for your experiment ' . $counter),
                    'cols' => 50,
                    'rows' => 4
                ),
                '#title' => t('Description for Experiment ') . $counter,
                '#states' => array(
                    'invisible' => array(
                        ':input[name=' . $namefield . ']' => array(
                            'value' => ""
                        )
                    )
                )
            );
          }
        $first_experiemnt = FALSE;
      }
    $form['solution_provider_uid'] = array(
        '#type' => 'radios',
        '#title' => t('Do you want to provide the solution'),
        '#options' => array(
            '1' => 'Yes',
            '2' => 'No'
        ),
        '#required' => TRUE,
        '#default_value' => '1',
        '#description' => 'If you dont want to provide the solution then it will be opened for the community, anyone may come forward and provide the solution.'
    );
    $form['solution_display'] = array(
        '#type' => 'hidden',
        '#title' => t('Do you want to display the solution on the www.r.fossee.in website'),
        '#options' => array(
            '1' => 'Yes'
        ),
        '#required' => TRUE,
        '#default_value' => '1',
        '#description' => 'If yes, solutions will be made available to everyone for downloading.',
        '#disabled' => FALSE
    );
    $form['sample_syllabus_file'] = array(
        '#type' => 'item',
        '#title' => t('<h5>Ideal Sample Lab Migration Submission</h5>'),
        '#markup' => t('Kindly refer to the ') . t('<a href= "https://r.fossee.in/lab-migration/lab-migration-run/12" target="_blank">Sample Lab Migration (Statistical Quality Control using R)</a> and <a href= "https://r.fossee.in/lab-migration/lab-migration-run/6" target="_blank">Sample Lab Migration (Analysis using R)</a>') . '' . t(' to know the ideal submission.')
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit')
    );
    return $form;
  }
function lab_migration_proposal_form_validate($form, &$form_state)
  {
    if (!preg_match('/^[0-9\ \+]{0,15}$/', $form_state['values']['contact_ph']))
      {
        $form_state->setErrorByName('contact_ph', t('Invalid contact phone number'));
      }
    if ($form_state['values']['country'] == 'Others')
      {
        if ($form_state['values']['other_country'] == '')
          {
            $form_state->setErrorByName('other_country', t('Enter country name'));
            // $form_state['values']['country'] = $form_state['values']['other_country'];
          }
        else
          {
            $form_state['values']['country'] = $form_state['values']['other_country'];
          }
        if ($form_state['values']['other_state'] == '')
          {
            $form_state->setErrorByName('other_state', t('Enter state name'));
            // $form_state['values']['country'] = $form_state['values']['other_country'];
          }
        else
          {
            $form_state['values']['all_state'] = $form_state['values']['other_state'];
          }
        if ($form_state['values']['other_city'] == '')
          {
            $form_state->setErrorByName('other_city', t('Enter city name'));
            // $form_state['values']['country'] = $form_state['values']['other_country'];
          }
        else
          {
            $form_state['values']['city'] = $form_state['values']['other_city'];
          }
      }
    else
      {
        if ($form_state['values']['country'] == '')
          {
            $form_state->setErrorByName('country', t('Select country name'));
            // $form_state['values']['country'] = $form_state['values']['other_country'];
          }
        if ($form_state['values']['all_state'] == '')
          {
            $form_state->setErrorByName('all_state', t('Select state name'));
            // $form_state['values']['country'] = $form_state['values']['other_country'];
          }
        if ($form_state['values']['city'] == '')
          {
            $form_state->setErrorByName('city', t('Select city name'));
            // $form_state['values']['country'] = $form_state['values']['other_country'];
          }
      }
    for ($counter = 1; $counter <= 15; $counter++)
      {
        $experiment_field_name = 'lab_experiment-' . $counter;
        $experiment_description = 'lab_experiment_description-' . $counter;
        if (strlen(trim($form_state['values'][$experiment_field_name])) >= 1)
          {
            if (strlen(trim($form_state['values'][$experiment_description])) <= 49)
              {
                $form_state->setErrorByName($experiment_description, t('Description should be minimum of 50 characters'));
              }
          }
      }
    if ($form_state['values']['version'] == 'olderversion')
      {
        if ($form_state['values']['older'] == '')
          {
            $form_state->setErrorByName('older', t('Please provide valid version'));
          }
      }

    if (isset($_FILES['files']))
    {
        /* check if atleast one source or result file is uploaded */
        if (!($_FILES['files']['name']['syllabus_copy_file']))
            $form_state->setErrorByName('syllabus_copy_file', t('Please upload pdf file.'));
        /* check for valid filename extensions */
        foreach ($_FILES['files']['name'] as $file_form_name => $file_name)
        {
            if ($file_name)
            {
                /* checking file type */
                if (strstr($file_form_name, 'syllabus'))
                    $file_type = 'S';
                else
                    $file_type = 'U';
                $allowed_extensions_str = '';
                switch ($file_type)
                {
                    case 'S':
                        $allowed_extensions_str = \Drupal::config('lab_migration.settings')->get('lab_migration_syllabus_file_extensions');
                        break;
                } //$file_type
                $allowed_extensions = explode(',', $allowed_extensions_str);
                $allowd_file = strtolower($_FILES['files']['name'][$file_form_name]);
                $allowd_files = explode('.', $allowd_file);
                $temp_extension = end($allowd_files);
                if (!in_array($temp_extension, $allowed_extensions))
                    $form_state->setErrorByName($file_form_name, t('Only file with ' . $allowed_extensions_str . ' extensions can be uploaded.'));
                if ($_FILES['files']['size'][$file_form_name] <= 0)
                    $form_state->setErrorByName($file_form_name, t('File size cannot be zero.'));
                /* check if valid file name */
                if (!lab_migration_check_valid_filename($_FILES['files']['name'][$file_form_name]))
                    $form_state->setErrorByName($file_form_name, t('Invalid file name specified. Only alphabets and numbers are allowed as a valid filename.'));
            } //$file_name
        } //$_FILES['files']['name'] as $file_form_name => $file_name
    } //isset($_FILES['files'])

    return;
  }
function lab_migration_proposal_form_submit($form, &$form_state)
  {
    $user = \Drupal::currentUser();
    if (!$user->uid)
      {
        \Drupal::messenger()->addError('It is mandatory to login on this website to access the proposal form');
        return;
      }
    $solution_provider_uid = 0;
    $solution_status = 0;
    $solution_provider_name_title = '';
    $solution_provider_name = '';
    $solution_provider_contact_ph = '';
    $solution_provider_department = '';
    $solution_provider_university = '';
    $syllabus_copy_file_path = '';
    if ($form_state['values']['solution_provider_uid'] == "1")
      {
        $solution_provider_uid = $user->uid;
        $solution_status = 1;
        $solution_provider_name_title = $form_state['values']['name_title'];
        $solution_provider_name = $form_state['values']['name'];
        $solution_provider_contact_ph = $form_state['values']['contact_ph'];
        $solution_provider_department = $form_state['values']['department'];
        $solution_provider_university = $form_state['values']['university'];
      }
    else
      {
        $solution_provider_uid = 0;
      }
    $solution_display = 0;
    if ($form_state['values']['solution_display'] == "1")
        $solution_display = 1;
    else
        $solution_display = 1;
    if ($form_state['values']['version'] == 'olderversion')
      {
        $form_state['values']['version'] = $form_state['values']['older'];
      }
    /* inserting the user proposal */
    $v = $form_state["values"];
    $lab_title = $v['lab_title'];
    $proposar_name = $v['name_title']. ' ' . $v['name'];
    $university = $v['university'];    
    $directory_name = _lm_dir_name($lab_title, $proposar_name, $university);
    $result = "INSERT INTO {lab_migration_proposal} 
    (uid, approver_uid, name_title, name, contact_ph, department, university, city, pincode, state, country, operating_system, r_version, syllabus_link, lab_title, approval_status, solution_status, solution_provider_uid, solution_display, creation_date, approval_date, solution_date, solution_provider_name_title, solution_provider_name, solution_provider_contact_ph, solution_provider_department, solution_provider_university, directory_name,syllabus_copy_file_path) VALUES
    (:uid, :approver_uid, :name_title, :name, :contact_ph, :department, :university, :city, :pincode, :state, :country, :operating_system, 
     :r_version, :syllabus_link, :lab_title, :approval_status, :solution_status, :solution_provider_uid, :solution_display, :creation_date, 
     :approval_date, :solution_date, :solution_provider_name_title, :solution_provider_name,
      :solution_provider_contact_ph, :solution_provider_department, :solution_provider_university, :directory_name,:syllabus_copy_file_path)";
    $args = array(
        ":uid" => $user->uid,
        ":approver_uid" => 0,
        ":name_title" => $v['name_title'],
        ":name" => $v['name'],
        ":contact_ph" => $v['contact_ph'],
        ":department" => $v['department'],
        ":university" => $v['university'],
        ":city" => $v['city'],
        ":pincode" => $v['pincode'],
        ":state" => $v['all_state'],
        ":country" => $v['country'],
        ":operating_system" => $v['operating_system'],
        ":r_version" => $form_state['values']['version'],
        ":syllabus_link" => $v['syllabus_link'],
        ":lab_title" => $v['lab_title'],
        ":approval_status" => 0,
        ":solution_status" => $solution_status,
        ":solution_provider_uid" => $solution_provider_uid,
        ":solution_display" => $solution_display,
        ":creation_date" => time(),
        ":approval_date" => 0,
        ":solution_date" => 0,
        ":solution_provider_name_title" => $solution_provider_name_title,
        ":solution_provider_name" => $solution_provider_name,
        ":solution_provider_contact_ph" => $solution_provider_contact_ph,
        ":solution_provider_department" => $solution_provider_department,
        ":solution_provider_university" => $solution_provider_university,
        ":directory_name" => $directory_name,
        ":syllabus_copy_file_path" => "",
    );
    $proposal_id = \Drupal::database()->query($result, $args, $result);
    $root_path = lab_migration_path();
    $dest_path = $proposal_id . '/';
    if (!is_dir($root_path . $dest_path))
        mkdir($root_path . $dest_path);
    /* uploading files */
    foreach ($_FILES['files']['name'] as $file_form_name => $file_name)
    {
        if ($file_name)
        {
            /* checking file type */
            $file_type = 'S';
            if (file_exists($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]))
            {
                \Drupal::messenger()->addError(t("Error uploading file. File !filename already exists.", array(
                    '!filename' => $_FILES['files']['name'][$file_form_name]
                )));
                return;
            } //file_exists($root_path . $dest_path . $_FILES['files']['name'][$file_form_name])
            /* uploading file */
            if (move_uploaded_file($_FILES['files']['tmp_name'][$file_form_name], $root_path . $dest_path . $_FILES['files']['name'][$file_form_name]))
            {
                $query = "UPDATE {lab_migration_proposal} SET syllabus_copy_file_path = :syllabus_copy_file_path WHERE id = :id";
                $args = array(
                    ":syllabus_copy_file_path" => $dest_path . $_FILES['files']['name'][$file_form_name],
                    ":id" => $proposal_id
                );
                $updateresult = \Drupal::database()->query($query, $args);
                \Drupal::messenger()->addStatus($file_name . ' uploaded successfully.');
            } //move_uploaded_file($_FILES['files']['tmp_name'][$file_form_name], $root_path . $dest_path . $_FILES['files']['name'][$file_form_name])
            else
            {
                \Drupal::messenger()->addError('Error uploading file : ' . $dest_path . '/' . $file_name);
            }
        } //$file_name
    } //$_FILES['files']['name'] as $file_form_name => $file_name
    if (!$proposal_id)
      {
        \Drupal::messenger()->addError(t('Error receiving your proposal. Please try again.'));
        return;
      }
    /* proposal id */
    //$proposal_id = db_last_insert_id('lab_migration_proposal', 'id');
    /* adding experiments */
    $number = 1;
    for ($counter = 1; $counter <= 15; $counter++)
      {
        $experiment_field_name = 'lab_experiment-' . $counter;
        $experiment_description = 'lab_experiment_description-' . $counter;
        if (strlen(trim($form_state['values'][$experiment_field_name])) >= 1)
          {
            //$query = "INSERT INTO {lab_migration_experiment} (proposal_id, directory_name, number, title,description) VALUES (:proposal_id, :directory_name, :number, :experiment_field_name,:description)";
             $query = "INSERT INTO {lab_migration_experiment} (proposal_id, number, title,description) VALUES (:proposal_id, :number, :experiment_field_name,:description)";
            $args = array(
                ":proposal_id" => $proposal_id,
               // ":directory_name" => $directory_name,
                ":number" => $number,
                ":experiment_field_name" => trim($form_state['values'][$experiment_field_name]),
                ":description" => trim($form_state['values'][$experiment_description])
            );
            $result = \Drupal::database()->query($query, $args);
            if (!$result)
              {
                \Drupal::messenger()->addError(t('Could not insert Title of the Experiment : ') . trim($form_state['values'][$experiment_field_name]));
              }
            else
              {
                $number++;
              }
          }
      }
    /* sending email */
    $email_to = $user->mail;
    $from = \Drupal::config('lab_migration.settings')->get('lab_migration_from_email');
    $bcc = \Drupal::config('lab_migration.settings')->get('lab_migration_emails');
    $cc = \Drupal::config('lab_migration.settings')->get('lab_migration_cc_emails');
    $param['proposal_received']['proposal_id'] = $proposal_id;
    $param['proposal_received']['user_id'] = $user->uid;
    $param['proposal_received']['headers'] = array(
        'From' => $from,
        'MIME-Version' => '1.0',
        'Content-Type' => 'text/plain; charset=UTF-8; format=flowed; delsp=yes',
        'Content-Transfer-Encoding' => '8Bit',
        'X-Mailer' => 'Drupal',
        'Cc' => $cc,
        'Bcc' => $bcc
    );
    if (!drupal_mail('lab_migration', 'proposal_received', $email_to, user_preferred_language($user), $param, $from, TRUE))
        \Drupal::messenger()->addError('Error sending email message.');
    \Drupal::messenger()->addStatus(t('We have received you Lab migration proposal. We will get back to you soon.'));
    RedirectResponse('');
  }

function _lm_dir_name($lab, $name, $university)
  {
    $lab_title = lm_ucname($lab);
    $proposar_name = lm_ucname($lab);
    $university_name = lm_ucname($university);
    $dir_name = $lab_title . " " . "by". " " . $proposar_name . ' ' . $university_name;
    $directory_name = str_replace("__", "_", str_replace(" ", "_", $dir_name));
    return $directory_name;
  }

function ajax_get_lm_city_list_callback($form, $form_state)
{
    $state_default_value = $form_state['values']['all_state'];
    $district_default_value = $form_state['values']['district'];
    if ($district_default_value != '0')
    {
        $form['city']['#options'] = _lab_migration_list_of_cities($state_default_value, $district_default_value);
        $commands[] = ajax_command_replace("#ajax-city-list-replace", \Drupal::service("renderer")->render($form['city']));
        $form['pincode']['#options'] =  array('0' => '- Select -');
        $commands[] = ajax_command_replace("#ajax-pincode-list-replace", \Drupal::service("renderer")->render($form['pincode']));
    }else{
        $form['city']['#options'] = array('0' => '- Select -');
        $commands[] = ajax_command_replace("#ajax-city-list-replace", \Drupal::service("renderer")->render($form['city']));
    }
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}
function ajax_get_lm_district_list_callback($form, $form_state)
{
    $state_default_value = $form_state['values']['all_state'];
    if ($state_default_value != '0')
    {
        $form['district']['#options'] = _lab_migration_list_of_district($state_default_value);
        $commands[] = ajax_command_replace("#ajax-district-list-replace", \Drupal::service("renderer")->render($form['district']));
        $form['pincode']['#options'] =  array('0' =>'- Select -');
        $commands[] = ajax_command_replace("#ajax-pincode-list-replace", \Drupal::service("renderer")->render($form['pincode']));
        $form['city']['#options'] = array('0' => '- Select -');
        $commands[] = ajax_command_replace("#ajax-city-list-replace", \Drupal::service("renderer")->render($form['city']));
    }else{
        $form['district']['#options'] = array('0' => '- Select -');
        $commands[] = ajax_command_replace("#ajax-district-list-replace", \Drupal::service("renderer")->render($form['district']));
        $form['pincode']['#options'] =  array('0' =>'- Select -');
        $commands[] = ajax_command_replace("#ajax-pincode-list-replace", \Drupal::service("renderer")->render($form['pincode']));
        $form['city']['#options'] = array('0' => '- Select -');
        $commands[] = ajax_command_replace("#ajax-city-list-replace", \Drupal::service("renderer")->render($form['city']));
    }
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}
function ajax_get_lm_city_pincode_list_callback($form, $form_state)
{
    $city_default_value = $form_state['values']['city'];
    $state_default_value = $form_state['values']['all_state'];
    $district_default_value = $form_state['values']['district'];
    if ($city_default_value != '0')
    {
        $form['pincode']['#options'] = _lab_migration_list_of_city_pincode($city_default_value,$state_default_value,$district_default_value);
        $commands[] = ajax_command_replace("#ajax-pincode-list-replace", \Drupal::service("renderer")->render($form['pincode']));
    }else{
        $form['pincode']['#options'] =  array('0' => '- Select -');
        $commands[] = ajax_command_replace("#ajax-pincode-list-replace", \Drupal::service("renderer")->render($form['pincode']));
    }
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}