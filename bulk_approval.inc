<?php
function lab_migration_bulk_approval_form($form, &$form_state)
  {
    $options_first = _bulk_list_of_labs();
    $options_two = _ajax_bulk_get_experiment_list();
    $selected = isset($form_state['values']['lab']) ? $form_state['values']['lab'] : key($options_first);
    $select_two = isset($form_state['values']['lab_experiment_list']) ? $form_state['values']['lab_experiment_list'] : key($options_two);
    $form = array();
    $form['lab'] = array(
        '#type' => 'select',
        '#title' => t('Title of the lab'),
        '#options' => _bulk_list_of_labs(),
        '#default_value' => $selected,
        '#ajax' => array(
            'callback' => 'ajax_bulk_experiment_list_callback'
        ),
        '#suffix' => '<div id="ajax_selected_lab"></div><div id="ajax_selected_lab_pdf"></div>'
    );
    $form['lab_actions'] = array(
        '#type' => 'select',
        '#title' => t('Please select action for Entire Lab'),
        '#options' => _bulk_list_lab_actions(),
        '#default_value' => 0,
        '#prefix' => '<div id="ajax_selected_lab_action" style="color:red;">',
        '#suffix' => '</div>',
        '#states' => array(
            'invisible' => array(
                ':input[name="lab"]' => array(
                    'value' => 0
                )
            )
        )
    );
    $form['lab_experiment_list'] = array(
        '#type' => 'select',
        '#title' => t('Titile of the experiment'),
        '#options' => _ajax_bulk_get_experiment_list($selected),
        '#default_value' => isset($form_state['values']['lab_experiment_list']) ? $form_state['values']['lab_experiment_list'] : '',
        '#ajax' => array(
            'callback' => 'ajax_bulk_solution_list_callback'
        ),
        '#prefix' => '<div id="ajax_selected_experiment">',
        '#suffix' => '</div>',
        '#states' => array(
            'invisible' => array(
                ':input[name="lab"]' => array(
                    'value' => 0
                )
            )
        )
    );
    $form['download_experiment'] = array(
        '#type' => 'item',
        '#markup' => '<div id="ajax_download_experiment"></div>'
    );
    $form['lab_experiment_actions'] = array(
        '#type' => 'select',
        '#title' => t('Please select action for Entire Experiment'),
        '#options' => _bulk_list_experiment_actions(),
        '#default_value' => 0,
        '#prefix' => '<div id="ajax_selected_lab_experiment_action" style="color:red;">',
        '#suffix' => '</div>',
        //'#states' => array('invisible' => array(':input[name="lab"]' => array('value' => 0),),),  
        '#states' => array(
            'invisible' => array(
                array(
                    array(
                        ':input[name="lab"]' => array(
                            'value' => 0
                        )
                    ),
                    'or',
                    array(
                        ':input[name="lab_actions"]' => array(
                            'value' => 0
                        )
                    )
                )
            )
        )
    );
    $form['lab_solution_list'] = array(
        '#type' => 'select',
        '#title' => t('Solution'),
        '#options' => _ajax_bulk_get_solution_list($select_two),
        '#default_value' => isset($form_state['values']['lab_solution_list']) ? $form_state['values']['lab_solution_list'] : '',
        '#ajax' => array(
            'callback' => 'ajax_bulk_solution_files_callback'
        ),
        '#prefix' => '<div id="ajax_selected_solution">',
        '#suffix' => '</div>',
        '#states' => array(
            'invisible' => array(
                ':input[name="lab"]' => array(
                    'value' => 0
                )
            )
        )
    );
    $form['lab_experiment_solution_actions'] = array(
        '#type' => 'select',
        '#title' => t('Please select action for solution'),
        '#options' => _bulk_list_solution_actions(),
        '#default_value' => 0,
        '#prefix' => '<div id="ajax_selected_lab_experiment_solution_action" style="color:red;">',
        '#suffix' => '</div>',
        '#states' => array(
            'invisible' => array(
                ':input[name="lab"]' => array(
                    'value' => 0
                )
            )
        )
    );
    $form['download_solution'] = array(
        '#type' => 'item',
        '#markup' => '<div id="ajax_download_experiment_solution"></div>'
    );
    $form['edit_solution'] = array(
        '#type' => 'item',
        '#markup' => '<div id="ajax_edit_experiment_solution"></div>'
    );
    $form['solution_files'] = array(
        '#type' => 'item',
        //'#title' => t('List of solution_files'),
        '#markup' => '<div id="ajax_solution_files"></div>',
        '#states' => array(
            'invisible' => array(
                ':input[name="lab"]' => array(
                    'value' => 0
                )
            )
        )
    );
    $form['message'] = array(
        '#type' => 'textarea',
        '#title' => t('If Dis-Approved please specify reason for Dis-Approval'),
        '#prefix' => '<div id= "message_submit">',
        '#states' => array(
            'visible' => array(
                array(
                    array(
                        ':input[name="lab_actions"]' => array(
                            'value' => 3
                        )
                    ),
                    'or',
                    array(
                        ':input[name="lab_experiment_actions"]' => array(
                            'value' => 3
                        )
                    ),
                    'or',
                    array(
                        ':input[name="lab_experiment_solution_actions"]' => array(
                            'value' => 3
                        )
                    ),
                    'or',
                    array(
                        ':input[name="lab_actions"]' => array(
                            'value' => 4
                        )
                    )
                )
            ),
            'required' => array(
                array(
                    array(
                        ':input[name="lab_actions"]' => array(
                            'value' => 3
                        )
                    ),
                    'or',
                    array(
                        ':input[name="lab_experiment_actions"]' => array(
                            'value' => 3
                        )
                    ),
                    'or',
                    array(
                        ':input[name="lab_experiment_solution_actions"]' => array(
                            'value' => 3
                        )
                    ),
                    'or',
                    array(
                        ':input[name="lab_actions"]' => array(
                            'value' => 4
                        )
                    )
                )
            )
        )
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit'),
        '#suffix' => '</div>',
        '#states' => array(
            'invisible' => array(
                ':input[name="lab"]' => array(
                    'value' => 0
                )
            )
        )
    );
    return $form;
  }
/**
 * Ajax callback triggered by select.
 */
function ajax_bulk_experiment_list_callback($form, $form_state)
  {
    $commands = array();
    $lab_default_value = $form_state['values']['lab'];
    if ($lab_default_value != 0)
      {
        // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $commands[] = ajax_command_html('#ajax_selected_lab', l('Download', 'lab-migration/full-download/lab/' . $lab_default_value) . ' ' . t('(Download all the approved and unapproved solutions of the entire lab)'));

        /*$commands[] = ajax_command_html('#ajax_selected_lab_pdf', l('Download PDF', 'lab_migration/generate_lab/' . $lab_default_value . '/1') . 
        ' ' . t('(Download PDF of all the approved and unapproved solution of the entire lab)'));  */
        $form['lab_actions']['#options'] = _bulk_list_lab_actions();
        $form['lab_experiment_list']['#options'] = _ajax_bulk_get_experiment_list($lab_default_value);
        $commands[] = ajax_command_data('#ajax_selected_lab', 'form_state_value_select', $form_state['values']['lab_experiment_list']);
        $commands[] = ajax_command_replace('#ajax_selected_experiment', \Drupal::service("renderer")->render($form['lab_experiment_list']));
        $commands[] = ajax_command_replace('#ajax_selected_lab_action', \Drupal::service("renderer")->render($form['lab_actions']));
        $commands[] = ajax_command_html('#ajax_selected_solution', '');
        $commands[] = ajax_command_html('#ajax_selected_lab_experiment_action', '');
        $commands[] = ajax_command_html('#ajax_selected_lab_experiment_solution_action', '');
        $commands[] = ajax_command_html('#ajax_solution_files', '');
        $commands[] = ajax_command_html('#ajax_download_experiment_solution', '');
        $commands[] = ajax_command_html('#ajax_edit_experiment_solution', '');
      }
    else
      {
        $commands[] = ajax_command_html('#ajax_selected_lab', '');
        $commands[] = ajax_command_html('#ajax_selected_lab_pdf', '');
        $commands[] = ajax_command_data('#ajax_selected_lab', 'form_state_value_select', $form_state['values']['lab']);
        $commands[] = ajax_command_html('#ajax_selected_experiment', '');
        $commands[] = ajax_command_html('#ajax_selected_lab_action', '');
        $commands[] = ajax_command_html('#ajax_selected_lab_experiment_action', '');
        $commands[] = ajax_command_html('#ajax_download_experiment', '');
        $commands[] = ajax_command_html('#ajax_selected_lab_experiment_solution_action', '');
        $commands[] = ajax_command_html('#ajax_solution_files', '');
        $commands[] = ajax_command_html('#ajax_download_experiment_solution', '');
        $commands[] = ajax_command_html('#ajax_edit_experiment_solution', '');
      }
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
  }
function ajax_bulk_solution_list_callback($form, $form_state)
  {
    $commands = array();
    $experiment_list_default_value = $form_state['values']['lab_experiment_list'];
    //var_dump($lab_default_value);
    if ($experiment_list_default_value != 0)
      {
        $form['lab_experiment_actions']['#options'] = _bulk_list_experiment_actions();
        $form['lab_solution_list']['#options'] = _ajax_bulk_get_solution_list($experiment_list_default_value);
        // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $commands[] = ajax_command_html('#ajax_download_experiment', l('Download Experiment', 'lab-migration/full-download/experiment/' . $experiment_list_default_value));

        $commands[] = ajax_command_data('#ajax_selected_experiment', 'form_state_value_select', $form_state['values']['lab_experiment_list']);
        $commands[] = ajax_command_html('#ajax_selected_experiment', \Drupal::service("renderer")->render($form['lab_experiment_list']));
        $commands[] = ajax_command_html('#ajax_selected_lab_experiment_action', \Drupal::service("renderer")->render($form['lab_experiment_actions']));
        $commands[] = ajax_command_html('#ajax_selected_solution', \Drupal::service("renderer")->render($form['lab_solution_list']));
        $commands[] = ajax_command_html('#ajax_selected_lab_experiment_solution_action', '');
        $commands[] = ajax_command_html('#ajax_solution_files', '');
        $commands[] = ajax_command_html('#ajax_download_experiment_solution', '');
        $commands[] = ajax_command_html('#ajax_edit_experiment_solution', '');
      }
    else
      {
        $commands[] = ajax_command_html('#ajax_download_experiment', '');
        $commands[] = ajax_command_html('#ajax_selected_lab_experiment_action', '');
        $commands[] = ajax_command_html('#ajax_selected_solution', '');
        $commands[] = ajax_command_html('#ajax_selected_lab_experiment_solution_action', '');
        $commands[] = ajax_command_html('#ajax_solution_files', '');
        $commands[] = ajax_command_html('#ajax_download_experiment_solution', '');
        $commands[] = ajax_command_html('#ajax_edit_experiment_solution', '');
        // $commands[] = ajax_command_replace('#ajax_selected_experiment',renderservice($form['lab_experiment_list']));
      }
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
  }
function ajax_bulk_solution_files_callback($form, $form_state)
  {
    $commands = array();
    $solution_list_default_value = $form_state['values']['lab_solution_list'];
    //var_dump($lab_default_value);
    if ($solution_list_default_value != 0)
      {
        $form['lab_experiment_solution_actions']['#options'] = _bulk_list_solution_actions();
        $commands[] = ajax_command_html('#ajax_selected_lab_experiment_solution_action', \Drupal::service("renderer")->render($form['lab_experiment_solution_actions']));
        /*************************************************************************************/
        //$solution_list_q = $injected_database->query("SELECT * FROM {lab_migration_solution_files} WHERE solution_id = %d", $form_state['values']['solution']);
        $query = \Drupal::database()->select('lab_migration_solution_files');
        $query->fields('lab_migration_solution_files');
        $query->condition('solution_id', $solution_list_default_value);
        $solution_list_q = $query->execute();
        if ($solution_list_q)
          {
            $solution_files_rows = array();
            while ($solution_list_data = $solution_list_q->fetchObject())
              {
                $solution_file_type = '';
                switch ($solution_list_data->filetype)
                {
                    case 'S':
                        $solution_file_type = 'Source or Main file';
                        break;
                    case 'R':
                        $solution_file_type = 'Result file';
                        break;
                    case 'X':
                        $solution_file_type = 'xcos file';
                        break;
                    default:
                        $solution_file_type = 'Unknown';
                        break;
                }
                // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $solution_files_rows[] = array(
//                     l($solution_list_data->filename, 'lab-migration/download/file/' . $solution_list_data->id),
//                     $solution_file_type
//                 );

                if (strlen($solution_list_data->pdfpath) >= 5)
                  {
                    $pdfname = substr($solution_list_data->pdfpath, strrpos($solution_list_data->pdfpath, '/') + 1);
                    // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $solution_files_rows[] = array(
//                         l($pdfname, 'lab-migration/download/pdf/' . $solution_list_data->id),
//                         "PDF File"
//                     );

                  }
              }
            /* dependency files */
            //$dependency_q = $injected_database->query("SELECT * FROM {lab_migration_solution_dependency} WHERE solution_id = %d", $form_state['values']['solution']);
            $query = \Drupal::database()->select('lab_migration_solution_dependency');
            $query->fields('lab_migration_solution_dependency');
            $query->condition('solution_id', $solution_list_default_value);
            $dependency_q = $query->execute();
            while ($dependency_data = $dependency_q->fetchObject())
              {
                //$dependency_files_q = $injected_database->query("SELECT * FROM {lab_migration_dependency_files} WHERE id = %d", $dependency_data->dependency_id);
                $query = \Drupal::database()->select('lab_migration_dependency_files');
                $query->fields('lab_migration_dependency_files');
                $query->condition('id', $dependency_data->dependency_id);
                $dependency_files_q = $query->execute();
                $dependency_files_data = $dependency_files_q->fetchObject();
                $solution_file_type = 'Dependency file';
                // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $solution_files_rows[] = array(
//                     l($dependency_files_data->filename, 'lab-migration/download/dependency/' . $dependency_files_data->dependency_id),
//                     $solution_file_type
//                 );

              }
            /* creating list of files table */
            $solution_files_header = array(
                'Filename',
                'Type'
            );
            // @FIXME
// _theme has been renamed to __theme and should NEVER be called directly.
// Calling __theme directly can alter the expected output and potentially
// introduce security issues (see https://www.drupal.org/node/2195739). You
// should use renderable arrays instead.
// 
// 
// @see https://www.drupal.org/node/2195739
// $solution_files = theme('table', array(
//                 'header' => $solution_files_header,
//                 'rows' => $solution_files_rows
//             ));

          }
        $form['solution_files']['#title'] = 'List of solution files';
        $form['solution_files']['#markup'] = $solution_files;
        // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $commands[] = ajax_command_html('#ajax_download_experiment_solution', l('Download Solution', 'lab-migration/download/solution/' . $solution_list_default_value));

        // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $commands[] = ajax_command_html('#ajax_edit_experiment_solution', l('Edit Solution', 'lab-migration/code-approval/editcode/' . $solution_list_default_value));

        // $commands[] = ajax_command_html('#ajax_solution_files', $solution_files);
        $commands[] = ajax_command_html('#ajax_solution_files', \Drupal::service("renderer")->render($form['solution_files']));
        /*************************************************************************************/
      }
    else
      {
        $commands[] = ajax_command_html('#ajax_selected_lab_experiment_solution_action', '');
        $commands[] = ajax_command_html('#ajax_download_experiment_solution', '');
        $commands[] = ajax_command_html('#ajax_edit_experiment_solution', '');
        $commands[] = ajax_command_html('#ajax_solution_files', '');
      }
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
  }
/************************************************************/
function lab_migration_bulk_approval_form_submit($form, &$form_state)
  {
    $user = \Drupal::currentUser();
    $root_path = lab_migration_path();
    if ($form_state['clicked_button']['#value'] == 'Submit')
      {
        if ($form_state['values']['lab'])
            //lab_migration_del_lab_pdf($form_state['values']['lab']);
        if (\Drupal::currentUser()->hasPermission('lab migration bulk manage code'))
          {
            $query = \Drupal::database()->select('lab_migration_proposal');
            $query->fields('lab_migration_proposal');
            $query->condition('id', $form_state['values']['lab']);
            $user_query = $query->execute();
            $user_info = $user_query->fetchObject();
            $user_data = \Drupal::entityTypeManager()->getStorage('user')->load($user_info->uid);
            if (($form_state['values']['lab_actions'] == 1) && ($form_state['values']['lab_experiment_actions'] == 0) && ($form_state['values']['lab_experiment_solution_actions'] == 0))
              {
                /* approving entire lab */
                //   $experiment_q = $injected_database->query("SELECT * FROM {lab_migration_experiment} WHERE proposal_id = %d", $form_state['values']['lab']);
                $query = \Drupal::database()->select('lab_migration_experiment');
                $query->fields('lab_migration_experiment');
                $query->condition('proposal_id', $form_state['values']['lab']);
                $query->orderBy('number', 'ASC');
                $experiment_q = $query->execute();
                $experiment_list = '';
                while ($experiment_data = $experiment_q->fetchObject())
                  {
                    //  $injected_database->query("UPDATE {lab_migration_solution} SET approval_status = 1, approver_uid = %d WHERE experiment_id = %d AND approval_status = 0", $user->uid, $experiment_data->id);
                    \Drupal::database()->query("UPDATE {lab_migration_solution} SET approval_status = 1, approver_uid = :approver_uid WHERE experiment_id = :experiment_id AND approval_status = 0", array(
                        ':approver_uid' => $user->uid,
                        ':experiment_id' => $experiment_data->id
                    ));
                    $experiment_list .= '<p>' . $experiment_data->number . ') ' . $experiment_data->title . '<br> Description :  ' . $experiment_data->description . '<br>';
                    $experiment_list .= ' ';
                    $experiment_list .= '</p>';
                  }
                \Drupal::messenger()->addStatus(t('Approved Entire Lab.'));
                /* email */
                // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $email_subject = t('[!site_name] Your uploaded Lab Migration solutions have been approved', array(
//                     '!site_name' => $config->get('site_name', '')
//                 ));

                // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $email_body = array(
//                     0 => t('
// 
// Dear !user_name,
// 
// Your all the uploaded solutions for the Lab with the below detail has been approved:
// 
// Title of Lab:' . $user_info->lab_title . '
// 
// List of experiments: ' . $experiment_list . '
// 
// Best Wishes,
// 
// !site_name Team,
// FOSSEE,IIT Bombay', array(
//                         '!site_name' => $config->get('site_name', ''),
//                         '!user_name' => $user_data->name
//                     ))
//                 );

              }
            elseif (($form_state['values']['lab_actions'] == 2) && ($form_state['values']['lab_experiment_actions'] == 0) && ($form_state['values']['lab_experiment_solution_actions'] == 0))
              {
                /* pending review entire lab */
                //$experiment_q = $injected_database->query("SELECT * FROM {lab_migration_experiment} WHERE proposal_id = %d", $form_state['values']['lab']);
                $experiment_q = \Drupal::database()->query("SELECT * FROM {lab_migration_experiment} WHERE proposal_id = :proposal_id", array(
                    ':proposal_id' => $form_state['values']['lab']
                ));
                while ($experiment_data = $experiment_q->fetchObject())
                  {
                    //$injected_database->query("UPDATE {lab_migration_solution} SET approval_status = 0 WHERE experiment_id = %d", $experiment_data->id);
                    \Drupal::database()->query("UPDATE {lab_migration_solution} SET approval_status = 0 WHERE experiment_id = :experiment_id", array(
                        ":experiment_id" => $experiment_data->id
                    ));
                  }
                \Drupal::messenger()->addStatus(t('Pending Review Entire Lab.'));
                /* email */
                // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $email_subject = t('[!site_name] Your uploaded Lab Migration solutions have been marked as pending', array(
//                     '!site_name' => $config->get('site_name', '')
//                 ));

                // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $email_body = array(
//                     0 => t('
// 
// Dear !user_name,
// 
// Your all the uploaded solutions for the Lab with Title: ' . $user_info->lab_title . ' have been marked as pending to be reviewed.
// 
// You will be able to see the solutions after they have been approved by one of our reviewers.
// 
// Best Wishes,
// 
// !site_name Team,
// FOSSEE,IIT Bombay', array(
//                         '!site_name' => $config->get('site_name', ''),
//                         '!user_name' => $user_data->name
//                     ))
//                 );

                /* email */
                /* $email_subject = t('Your uploaded Lab Migration solutions have been marked as pending');
                $email_body = array(0 => t('Your all the uploaded solutions for the Lab have been marked as pending to be review. You will be able to see the solutions after they have been approved by one of our reviewers.'));*/
              }
            elseif (($form_state['values']['lab_actions'] == 3) && ($form_state['values']['lab_experiment_actions'] == 0) && ($form_state['values']['lab_experiment_solution_actions'] == 0))
              {
                
                if (strlen(trim($form_state['values']['message'])) <= 30)
                  {
                    $form_state->setErrorByName('message', t(''));
                    \Drupal::messenger()->addError("Please mention the reason for disapproval. Minimum 30 character required");
                    return;
                  }
                if (!\Drupal::currentUser()->hasPermission('lab migration bulk delete code'))
                  {
                    \Drupal::messenger()->addError(t('You do not have permission to Bulk Dis-Approved and Deleted Entire Lab.'));
                    return;
                  }
                if (lab_migration_delete_lab($form_state['values']['lab']))
                  {
                    \Drupal::messenger()->addStatus(t('Dis-Approved and Deleted Entire Lab.'));
                  }
                else
                  {
                    \Drupal::messenger()->addError(t('Error Dis-Approving and Deleting Entire Lab.'));
                  }
                /* email */
                // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $email_subject = t('[!site_name] Your uploaded Lab Migration solutions have been marked as dis-approved', array(
//                     '!site_name' => $config->get('site_name', '')
//                 ));

                // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $email_body = array(
//                     0 => t('
// 
// Dear !user_name,
// 
// Your all the uploaded solutions for the whole Lab with Title: ' . $user_info->lab_title . ' have been marked as dis-approved.
// 
// Reason for dis-approval: ' . $form_state['values']['message'] . '
// 
// Best Wishes,
// 
// !site_name Team,
// FOSSEE,IIT Bombay', array(
//                         '!site_name' => $config->get('site_name', ''),
//                         '!user_name' => $user_data->name
//                     ))
//                 );

                /* email */
                /* $email_subject = t('Your uploaded Lab Migration solutions have been marked as dis-approved');
                $email_body = array(0 =>t('Your all the uploaded solutions for the whole Lab have been marked as dis-approved.
                
                Reason for dis-approval:
                
                ' . $form_state['values']['message']));*/
              }
            elseif (($form_state['values']['lab_actions'] == 4) && ($form_state['values']['lab_experiment_actions'] == 0) && ($form_state['values']['lab_experiment_solution_actions'] == 0))
              {
                if (strlen(trim($form_state['values']['message'])) <= 30)
                  {
                    $form_state->setErrorByName('message', t(''));
                    \Drupal::messenger()->addError("Please mention the reason for disapproval/deletion. Minimum 30 character required");
                    return;
                  }
                $query = \Drupal::database()->select('lab_migration_experiment');
                $query->fields('lab_migration_experiment');
                $query->condition('proposal_id', $form_state['values']['lab']);
                $query->orderBy('number', 'ASC');
                $experiment_q = $query->execute();
                $experiment_list = '';
                while ($experiment_data = $experiment_q->fetchObject())
                  {
                    $experiment_list .= '<p>' . $experiment_data->number . ') ' . $experiment_data->title . '<br> Description:  ' . $experiment_data->description . '<br>';
                    $experiment_list .= ' ';
                    $experiment_list .= '</p>';
                  }
                if (!\Drupal::currentUser()->hasPermission('lab migration bulk delete code'))
                  {
                    \Drupal::messenger()->addError(t('You do not have permission to Bulk Delete Entire Lab Including Proposal.'));
                    return;
                  }
                /* check if dependency files are present */
                $dep_q = \Drupal::database()->query("SELECT * FROM {lab_migration_dependency_files} WHERE proposal_id = :proposal_id", array(
                    ":proposal_id" => $form_state['values']['lab']
                ));
                if ($dep_data = $dep_q->fetchObject())
                  {
                    \Drupal::messenger()->addError(t("Cannot delete lab since it has dependency files that can be used by others. First delete the dependency files before deleting the lab."));
                    return;
                  }
                if (lab_migration_delete_lab($form_state['values']['lab']))
                  {
                    \Drupal::messenger()->addStatus(t('Dis-Approved and Deleted Entire Lab solutions.'));
                    $query = \Drupal::database()->select('lab_migration_proposal');
                    $query->fields('lab_migration_proposal');
                    $query->condition('id', $form_state['values']['lab']);
                    $proposal_q = $query->execute()->fetchObject();
                    $query = \Drupal::database()->select('lab_migration_experiment');
                    $query->fields('lab_migration_experiment');
                    $query->condition('proposal_id', $form_state['values']['lab']);
                    $experiment_q = $query->execute();
                    $experiment_data = $experiment_q->fetchObject();
                    $exp_path = $root_path . $proposal_q->directory_name . '/EXP' . $experiment_data->number;
                    $dir_path = $root_path . $proposal_q->directory_name;
                    if (is_dir($dir_path))
                      {
                        rmdir($exp_path);
                        $res = rmdir($dir_path);
                        if (!$res)
                          {
                            \Drupal::messenger()->addError(t("Cannot delete Lab directory: " . $dir_path . ". Please contact administrator."));
                            return;
                          }
                      }
                    else
                      {
                        \Drupal::messenger()->addStatus(t("Lab directory not present: " . $dir_path . ". Skipping deleting lab directory."));
                      }
                    /* deleting full proposal */
                    //$proposal_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE id = %d", $form_state['values']['lab']);
                    $proposal_q = \Drupal::database()->query("SELECT * FROM {lab_migration_proposal} WHERE id = :id", array(
                        ":id" => $form_state['values']['lab']
                    ));
                    $proposal_data = $proposal_q->fetchObject();
                    $proposal_id = $proposal_data->id;
                    \Drupal::database()->query("DELETE FROM {lab_migration_experiment} WHERE proposal_id = :proposal_id", array(
                        ":proposal_id" => $proposal_id
                    ));
                    \Drupal::database()->query("DELETE FROM {lab_migration_proposal} WHERE id = :id", array(
                        ":id" => $proposal_id
                    ));
                    \Drupal::messenger()->addStatus(t('Deleted Lab Proposal.'));
                    /* email */
                    // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $email_subject = t('[!site_name] Your uploaded Lab Migration solutions including the Lab proposal have been deleted', array(
//                         '!site_name' => $config->get('site_name', '')
//                     ));

                    // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $email_body = array(
//                         0 => t('
// 
// Dear ' . $proposal_data->name . ',
// 
// We regret to inform you that all the uploaded Experiments of your Lab with following details have been deleted permanently.
// 
// Title of Lab:' . $user_info->lab_title . '
// 
// List of experiments: ' . $experiment_list . '
// 
// Reason for dis-approval: ' . $form_state['values']['message'] . '
// 
// Best Wishes,
// 
// !site_name Team
// FOSSEE, IIT Bombay', array(
//                             '!site_name' => $config->get('site_name', ''),
//                             '!user_name' => $user_data->name
//                         ))
//                     );

                    /* email */
                    /*  $email_subject = t('Your uploaded Lab Migration solutions including the Lab proposal have been deleted');
                    $email_body = array(0 =>t('Your all the uploaded solutions including the Lab proposal have been deleted permanently.'));*/
                  }
                else
                  {
                    \Drupal::messenger()->addError(t('Error Dis-Approving and Deleting Entire Lab.'));
                  }
              }
            elseif (($form_state['values']['lab_actions'] == 0) && ($form_state['values']['lab_experiment_actions'] == 1) && ($form_state['values']['lab_experiment_solution_actions'] == 0))
              {
                \Drupal::database()->query("UPDATE {lab_migration_solution} SET approval_status = 1, approver_uid = :approver_uid WHERE experiment_id = :experiment_id AND approval_status = 0", array(
                    ":approver_uid" => $user->uid,
                    ":experiment_id" => $form_state['values']['lab_experiment_list']
                ));
                $query = \Drupal::database()->select('lab_migration_experiment');
                $query->fields('lab_migration_experiment');
                $query->condition('id', $form_state['values']['lab_experiment_list']);
                $query->orderBy('number', 'ASC');
                $experiment_q = $query->execute();
                $experiment_value = $experiment_q->fetchObject();
                $query = \Drupal::database()->select('lab_migration_solution');
                $query->fields('lab_migration_solution');
                $query->condition('experiment_id', $form_state['values']['lab_experiment_list']);
                $query->orderBy('code_number', 'ASC');
                $solution_q = $query->execute();
                $solution_value = $solution_q->fetchObject();
                \Drupal::messenger()->addStatus(t('Approved Entire Experiment.'));
                /* email */
                // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $email_subject = t('[!site_name] Your uploaded Lab Migration solution have been approved', array(
//                     '!site_name' => $config->get('site_name', '')
//                 ));

                // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $email_body = array(
//                     0 => t('
// 
// Dear !user_name,
// 
// Your Experiment for R Lab Migration with the following details is approved.
// 
// Experiment name: ' . $experiment_value->title . '
// Caption: ' . $solution_value->caption . '
// 
// Best Wishes,
// 
// !site_name Team,
// FOSSEE,IIT Bombay', array(
//                         '!site_name' => $config->get('site_name', ''),
//                         '!user_name' => $user_data->name
//                     ))
//                 );

                /* email */
                /* $email_subject = t('Your uploaded Lab Migration solutions have been approved');
                $email_body = array(0 =>t('Your all the uploaded solutions for the experiment have been approved.'));*/
              }
            elseif (($form_state['values']['lab_actions'] == 0) && ($form_state['values']['lab_experiment_actions'] == 2) && ($form_state['values']['lab_experiment_solution_actions'] == 0))
              {
                \Drupal::database()->query("UPDATE {lab_migration_solution} SET approval_status = 0 WHERE experiment_id = :experiment_id", array(
                    ":experiment_id" => $form_state['values']['lab_experiment_list']
                ));
                \Drupal::messenger()->addStatus(t('Entire Experiment marked as Pending Review.'));
                $query = \Drupal::database()->select('lab_migration_experiment');
                $query->fields('lab_migration_experiment');
                $query->condition('id', $form_state['values']['lab_experiment_list']);
                $query->orderBy('number', 'ASC');
                $experiment_q = $query->execute();
                $experiment_value = $experiment_q->fetchObject();
                $query = \Drupal::database()->select('lab_migration_solution');
                $query->fields('lab_migration_solution');
                $query->condition('experiment_id', $form_state['values']['lab_experiment_list']);
                $query->orderBy('code_number', 'ASC');
                $solution_q = $query->execute();
                $solution_value = $solution_q->fetchObject();
                /* email */
                // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $email_subject = t('[!site_name] Your uploaded Lab Migration solution have been marked as pending', array(
//                     '!site_name' => $config->get('site_name', '')
//                 ));

                // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $email_body = array(
//                     0 => t('
// 
// Dear !user_name,
// 
// Your all the uploaded solutions for the experiment have been marked as pending to be reviewed.
// 
// Experiment name: ' . $experiment_value->title . '
// Caption: ' . $solution_value->caption . '
// 
// Best Wishes,
// 
// !site_name Team,
// FOSSEE,IIT Bombay', array(
//                         '!site_name' => $config->get('site_name', ''),
//                         '!user_name' => $user_data->name
//                     ))
//                 );

                /* email */
                /*$email_subject = t('Your uploaded Lab Migration solutions have been marked as pending');
                $email_body = array(0 =>t('Your all the uploaded solutions for the experiment have been marked as pending to be review.'));*/
              }
            elseif (($form_state['values']['lab_actions'] == 0) && ($form_state['values']['lab_experiment_actions'] == 3) && ($form_state['values']['lab_experiment_solution_actions'] == 0))
              {
                if (strlen(trim($form_state['values']['message'])) <= 30)
                  {
                    $form_state->setErrorByName('message', t(''));
                    \Drupal::messenger()->addError("Please mention the reason for disapproval. Minimum 30 character required");
                    return;
                  }
                if (!\Drupal::currentUser()->hasPermission('lab migration bulk delete code'))
                  {
                    \Drupal::messenger()->addError(t('You do not have permission to Bulk Dis-Approved and Deleted Entire Experiment.'));
                    return;
                  }
                $query = \Drupal::database()->select('lab_migration_experiment');
                $query->fields('lab_migration_experiment');
                $query->condition('id', $form_state['values']['lab_experiment_list']);
                $query->orderBy('number', 'ASC');
                $experiment_q = $query->execute();
                $experiment_value = $experiment_q->fetchObject();
                $query = \Drupal::database()->select('lab_migration_solution');
                $query->fields('lab_migration_solution');
                $query->condition('experiment_id', $form_state['values']['lab_experiment_list']);
                $query->orderBy('code_number', 'ASC');
                $solution_q = $query->execute();
                $solution_value = $solution_q->fetchObject();
                if (lab_migration_delete_experiment($form_state['values']['lab_experiment_list']))
                  {
                    \Drupal::messenger()->addStatus(t('Dis-Approved and Deleted Entire Experiment.'));
                  }
                else
                  {
                    \Drupal::messenger()->addError(t('Error Dis-Approving and Deleting Entire Experiment.'));
                  }
                /* email */
                // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $email_subject = t('[!site_name] Your uploaded Lab Migration solutions have been marked as dis-approved', array(
//                     '!site_name' => $config->get('site_name', '')
//                 ));

                // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $email_body = array(
//                     0 => t('
// 
// Dear !user_name,
// 
// We regret to inform you that your experiment with the following details under R Lab Migration is disapproved and has been deleted.
// 
// Experiment name: ' . $experiment_value->title . '
// Caption: ' . $solution_value->caption . '
// 
// Reason for dis-approval: ' . $form_state['values']['message'] . '
// 
// Please resubmit the modified solution.
// 
// Best Wishes,
// 
// !site_name Team,
// FOSSEE,IIT Bombay', array(
//                         '!site_name' => $config->get('site_name', ''),
//                         '!user_name' => $user_data->name
//                     ))
//                 );

                /* email */
                /*$email_subject = t('Your uploaded Lab Migration solutions have been marked as dis-approved');
                $email_body = array(0 => t('Your uploaded solutions for the entire experiment have been marked as dis-approved.
                
                Reason for dis-approval:
                
                ' . $form_state['values']['message']));*/
              }
            elseif (($form_state['values']['lab_actions'] == 0) && ($form_state['values']['lab_experiment_actions'] == 0) && ($form_state['values']['lab_experiment_solution_actions'] == 1))
              {
                $query = \Drupal::database()->select('lab_migration_solution');
                $query->fields('lab_migration_solution');
                $query->condition('id', $form_state['values']['lab_solution_list']);
                $query->orderBy('code_number', 'ASC');
                $solution_q = $query->execute();
                $solution_value = $solution_q->fetchObject();
                $query = \Drupal::database()->select('lab_migration_experiment');
                $query->fields('lab_migration_experiment');
                $query->condition('id', $solution_value->experiment_id);
                $query->orderBy('number', 'ASC');
                $experiment_q = $query->execute();
                $experiment_value = $experiment_q->fetchObject();
                \Drupal::database()->query("UPDATE {lab_migration_solution} SET approval_status = 1, approver_uid = :approver_uid WHERE id = :id", array(
                    ":approver_uid" => $user->uid,
                    ":id" => $form_state['values']['lab_solution_list']
                ));
                \Drupal::messenger()->addStatus(t('Solution approved.'));
                /* email */
                // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $email_subject = t('[!site_name] Your uploaded Lab Migration solution has been approved', array(
//                     '!site_name' => $config->get('site_name', '')
//                 ));

                // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $email_body = array(
//                     0 => t('
// 
// Dear !user_name,
// 
// Your Experiment for R Lab Migration with the following details is approved.
// 
// Experiment name: ' . $experiment_value->title . '
// Caption: ' . $solution_value->caption . '
// 
// Best Wishes,
// 
// !site_name Team,
// FOSSEE,IIT Bombay', array(
//                         '!site_name' => $config->get('site_name', ''),
//                         '!user_name' => $user_data->name
//                     ))
//                 );

                /* email */
                /* $email_subject = t('Your uploaded Lab Migration solution has been approved');
                $email_body = array(0 =>t('Your uploaded solution has been approved.'));*/
              }
            elseif (($form_state['values']['lab_actions'] == 0) && ($form_state['values']['lab_experiment_actions'] == 0) && ($form_state['values']['lab_experiment_solution_actions'] == 2))
              {
                $query = \Drupal::database()->select('lab_migration_solution');
                $query->fields('lab_migration_solution');
                $query->condition('id', $form_state['values']['lab_solution_list']);
                $query->orderBy('code_number', 'ASC');
                $solution_q = $query->execute();
                $solution_value = $solution_q->fetchObject();
                $query = \Drupal::database()->select('lab_migration_experiment');
                $query->fields('lab_migration_experiment');
                $query->condition('id', $solution_value->experiment_id);
                $query->orderBy('number', 'ASC');
                $experiment_q = $query->execute();
                $experiment_value = $experiment_q->fetchObject();
                \Drupal::database()->query("UPDATE {lab_migration_solution} SET approval_status = 0 WHERE id = :id", array(
                    ":id" => $form_state['values']['lab_solution_list']
                ));
                \Drupal::messenger()->addStatus(t('Solution marked as Pending Review.'));
                /* email */
                // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $email_subject = t('[!site_name] Your uploaded Lab Migration solution has been marked as pending', array(
//                     '!site_name' => $config->get('site_name', '')
//                 ));

                // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $email_body = array(
//                     0 => t('
// 
// Dear !user_name,
// 
// Your all the uploaded solutions for the experiment have been marked as pending to be reviewed.
// 
// Experiment name: ' . $experiment_value->title . '
// Caption: ' . $solution_value->caption . '
// 
// Best Wishes,
// 
// !site_name Team,
// FOSSEE,IIT Bombay', array(
//                         '!site_name' => $config->get('site_name', ''),
//                         '!user_name' => $user_data->name
//                     ))
//                 );

                /* email */
                /*$email_subject = t('Your uploaded Lab Migration solution has been marked as pending');
                $email_body = array(0 =>t('Your uploaded solution has been marked as pending to be review.'));*/
              }
            elseif (($form_state['values']['lab_actions'] == 0) && ($form_state['values']['lab_experiment_actions'] == 0) && ($form_state['values']['lab_experiment_solution_actions'] == 3))
              {
                $query = \Drupal::database()->select('lab_migration_solution');
                $query->fields('lab_migration_solution');
                $query->condition('id', $form_state['values']['lab_solution_list']);
                $query->orderBy('code_number', 'ASC');
                $solution_q = $query->execute();
                $solution_value = $solution_q->fetchObject();
                $query = \Drupal::database()->select('lab_migration_experiment');
                $query->fields('lab_migration_experiment');
                $query->condition('id', $solution_value->experiment_id);
                $query->orderBy('number', 'ASC');
                $experiment_q = $query->execute();
                $experiment_value = $experiment_q->fetchObject();
                if (strlen(trim($form_state['values']['message'])) <= 30)
                  {
                    $form_state->setErrorByName('message', t(''));
                    \Drupal::messenger()->addError("Please mention the reason for disapproval. Minimum 30 character required");
                    return;
                  }
                if (lab_migration_delete_solution($form_state['values']['lab_solution_list']))
                  {
                    \Drupal::messenger()->addStatus(t('Solution Dis-Approved and Deleted.'));
                  }
                else
                  {
                    \Drupal::messenger()->addError(t('Error Dis-Approving and Deleting Solution.'));
                  }
                /* email */
                // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $email_subject = t('[!site_name] Your uploaded Lab Migration solution has been marked as dis-approved', array(
//                     '!site_name' => $config->get('site_name', '')
//                 ));

                // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $email_body = array(
//                     0 => t('
// 
// Dear !user_name,
// 
// We regret to inform you that your experiment with the following details under R Lab Migration is disapproved and has been deleted.
// 
// Experiment name: ' . $experiment_value->title . '
// Caption: ' . $solution_value->caption . '
// 
// Reason for dis-approval: ' . $form_state['values']['message'] . '
// 
// Please resubmit the modified solution.
// 
// Best Wishes,
// 
// !site_name Team,
// FOSSEE,IIT Bombay', array(
//                         '!site_name' => $config->get('site_name', ''),
//                         '!user_name' => $user_data->name
//                     ))
//                 );

                /* email */
                /* $email_subject = t('Your uploaded Lab Migration solution has been marked as dis-approved');
                $email_body = array(0 =>t('Your uploaded solution has been marked as dis-approved.
                
                Reason for dis-approval:
                
                ' . $form_state['values']['message']));*/
              }
            else
              {
                \Drupal::messenger()->addError(t('Please select only one action at a time'));
                return;
              }
            /** sending email when everything done **/
            if ($email_subject)
              {
                $email_to = $user_data->mail;
                $from = \Drupal::config('lab_migration.settings')->get('lab_migration_from_email');
                $bcc = \Drupal::config('lab_migration.settings')->get('lab_migration_emails');
                $cc = \Drupal::config('lab_migration.settings')->get('lab_migration_cc_emails');
                $param['standard']['subject'] = $email_subject;
                $param['standard']['body'] = $email_body;
                $param['standard']['headers'] = array(
                    'From' => $from,
                    'MIME-Version' => '1.0',
                    'Content-Type' => 'text/plain; charset=UTF-8; format=flowed; delsp=yes',
                    'Content-Transfer-Encoding' => '8Bit',
                    'X-Mailer' => 'Drupal',
                    'Cc' => $cc,
                    'Bcc' => $bcc
                );
                if (!drupal_mail('lab_migration', 'standard', $email_to, language_default(), $param, $from, TRUE))
                  {
                    \Drupal::messenger()->addError('Error sending email message.');
                  }
              }
          }
        else
          {
            \Drupal::messenger()->addError(t('You do not have permission to bulk manage code.'));
          }
      }
    return;
  }
function lab_migration_with_morefeature($key, &$message, $params)
  {
    if (isset($params['subject']))
      {
        $message['subject'] = $params['subject'];
      }
    if (isset($params['body']))
      {
        $message['body'][] = $params['body'];
      }
    if (isset($params['headers']) && is_array($params['headers']))
      {
        $message['headers'] += $params['headers'];
      }
  }
/**********************************************************/
function _bulk_list_of_labs()
  {
    $lab_titles = array(
        '0' => 'Please select...'
    );
    //$lab_titles_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE solution_display = 1 ORDER BY lab_title ASC");
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('solution_display', 1);
    $query->orderBy('lab_title', 'ASC');
    $lab_titles_q = $query->execute();
    while ($lab_titles_data = $lab_titles_q->fetchObject())
      {
        $lab_titles[$lab_titles_data->id] = $lab_titles_data->lab_title . ' (Proposed by ' . $lab_titles_data->name . ')';
      }
    return $lab_titles;
  }
function _ajax_bulk_get_experiment_list($lab_default_value = '')
  {
    $experiments = array(
        '0' => 'Please select...'
    );
    //$experiments_q = $injected_database->query("SELECT * FROM {lab_migration_experiment} WHERE proposal_id = %d ORDER BY number ASC", $proposal_id);
    $query = \Drupal::database()->select('lab_migration_experiment');
    $query->fields('lab_migration_experiment');
    $query->condition('proposal_id', $lab_default_value);
    $query->orderBy('number', 'ASC');
    $experiments_q = $query->execute();
    while ($experiments_data = $experiments_q->fetchObject())
      {
        $experiments[$experiments_data->id] = $experiments_data->number . '. ' . $experiments_data->title;
      }
    return $experiments;
  }
function _bulk_list_lab_actions()
  {
    $lab_actions = array(
        0 => 'Please select...'
    );
    $lab_actions[1] = 'Approve Entire Lab';
    $lab_actions[2] = 'Pending Review Entire Lab';
    $lab_actions[3] = 'Dis-Approve Entire Lab (This will delete all the solutions in the lab)';
    $lab_actions[4] = 'Delete Entire Lab Including Proposal';
    return $lab_actions;
  }
function _ajax_bulk_get_solution_list($lab_experiment_list = '')
  {
    $solutions = array(
        0 => 'Please select...'
    );
    // $solutions_q = $injected_database->query("SELECT * FROM {lab_migration_solution} WHERE experiment_id = %d ORDER BY
    //  CAST(SUBSTRING_INDEX(code_number, '.', 1) AS BINARY) ASC,
    //   CAST(SUBSTRING_INDEX(SUBSTRING_INDEX(code_number , '.', 2), '.', -1) AS UNSIGNED) ASC,
    //  CAST(SUBSTRING_INDEX(SUBSTRING_INDEX(code_number , '.', -1), '.', 1) AS UNSIGNED) ASC", $experiment_id);
    $query = \Drupal::database()->select('lab_migration_solution');
    $query->fields('lab_migration_solution');
    $query->condition('experiment_id', $lab_experiment_list);
    //$query->orderBy("CAST(SUBSTRING_INDEX(code_number, '.', 1) AS BINARY", "ASC");
    // $query->orderBy("CAST(SUBSTRING_INDEX(SUBSTRING_INDEX(code_number , '.', 2), '.', -1) AS UNSIGNED", "ASC");
    // $query->orderBy("CAST(SUBSTRING_INDEX(SUBSTRING_INDEX(code_number , '.', -1), '.', 1) AS UNSIGNED", "ASC");
    $solutions_q = $query->execute();
    while ($solutions_data = $solutions_q->fetchObject())
      {
        $solutions[$solutions_data->id] = $solutions_data->code_number . ' (' . $solutions_data->caption . ')';
      }
    return $solutions;
  }
function _bulk_list_experiment_actions()
  {
    $lab_experiment_actions = array(
        0 => 'Please select...'
    );
    $lab_experiment_actions[1] = 'Approve Entire Experiment';
    $lab_experiment_actions[2] = 'Pending Review Entire Experiment';
    $lab_experiment_actions[3] = 'Dis-Approve Entire Experiment (This will delete all the solutions in the experiment)';
    return $lab_experiment_actions;
  }
function _bulk_list_solution_actions()
  {
    $lab_solution_actions = array(
        0 => 'Please select...'
    );
    $lab_solution_actions[1] = 'Approve Entire Solution';
    $lab_solution_actions[2] = 'Pending Review Entire Solution';
    $lab_solution_actions[3] = 'Dis-approve Solution (This will delete the solution)';
    return $lab_solution_actions;
  }