<?php
/******************************************************************************/
/********************************* BULK APPROVAL ******************************/
/******************************************************************************/
function lab_migration_dependency_approval_form($form, $form_state)
  {
    /* default value for ahah fields */
    if (!isset($form_state['values']['dependency']))
      {
        $dependency_default_value = 0;
      }
    else
      {
        $dependency_default_value = $form_state['values']['dependency'];
      }
    $form['wrapper'] = array(
        '#type' => 'fieldset',
        '#title' => t('Bulk Manage Code'),
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
        '#prefix' => '<div id="run-wrapper">',
        '#suffix' => '</div>',
        '#tree' => TRUE
    );
    $form['wrapper']['dependency'] = array(
        '#type' => 'select',
        '#title' => t('Dependency'),
        '#options' => _list_of_dependencies(),
        '#default_value' => $dependency_default_value,
        '#tree' => TRUE,
        '#attributes' => array(
            'id' => 'dependancy'
        )
    );
    $form["wrapper"]['dependencyfiles'] = array(
        '#markup' => '<div id = "dependency-files"></div>'
    );
    $form['wrapper']['delete_dependency'] = array(
        '#type' => 'checkbox',
        "#description" => 'Please unlink the dependency from the above solutions before deleting it',
        '#title' => t('Delete Dependency'),
        '#prefix' => '<div id="delete-dependency-file">',
        '#attributes' => array(
            'id' => 'delete-dependancy'
        )
    );
    $form['wrapper']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit'),
        '#suffix' => '</div>'
    );
    return $form;
  }
function lab_migration_dependency_approval_ajax($item = "", $key = "")
  {
    $data = "";
    $dependency_default_value = $key;
    $solution_list = array();
    //$solution_id_q = $injected_database->query("SELECT * FROM {lab_migration_solution_dependency} WHERE dependency_id = %d", $dependency_default_value);
    $query = \Drupal::database()->select('lab_migration_solution_dependency');
    $query->fields('lab_migration_solution_dependency');
    $query->condition('dependency_id', $dependency_default_value);
    $solution_id_q = $query->execute();
    while ($solution_id_data = $solution_id_q->fetchObject())
      {
        //$solution_q = $injected_database->query("SELECT * FROM {lab_migration_solution} WHERE id = %d", $solution_id_data->solution_id);
        $query = \Drupal::database()->select('lab_migration_solution');
        $query->fields('lab_migration_solution');
        $query->condition('id', $solution_id_data->solution_id);
        $solution_q = $query->execute();
        $solution_data = $solution_q->fetchObject();
        //$experiment_q = $injected_database->query("SELECT * FROM {lab_migration_experiment} WHERE id = %d", $solution_data->experiment_id);
        $query = \Drupal::database()->select('lab_migration_experiment');
        $query->fields('lab_migration_experiment');
        $query->condition('id', $solution_data->experiment_id);
        $experiment_q = $query->execute();
        $experiment_data = $experiment_q->fetchObject();
        //$lab_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE id = %d", $experiment_data->proposal_id);
        $query = \Drupal::database()->select('lab_migration_proposal');
        $query->fields('lab_migration_proposal');
        $query->condition('id', $experiment_data->proposal_id);
        $lab_q = $query->execute();
        $lab_data = $lab_q->fetchObject();
        $solution_list[] = array(
            $solution_data->code_number,
            $experiment_data->number . ' . ' . $experiment_data->title,
            $lab_data->lab_title
        );
      }
    $solution_list_header = array(
        'Code',
        'Experiment',
        'Lab'
    );
    //$solution = theme_table($solution_list_header, $solution_list); 
    // @FIXME
// _theme has been renamed to __theme and should NEVER be called directly.
// Calling __theme directly can alter the expected output and potentially
// introduce security issues (see https://www.drupal.org/node/2195739). You
// should use renderable arrays instead.
// 
// 
// @see https://www.drupal.org/node/2195739
// $solution = theme('table', array(
//         'header' => $solution_list_header,
//         'rows' => $solution_list
//     ));

    $data .= $solution;
    echo $data;
  }
function lab_migration_dependency_approval_form_submit($form, &$form_state)
  {
    $user = \Drupal::currentUser();
    $root_path = lab_migration_path();
    if ($form_state['clicked_button']['#value'] == 'Submit')
      {
        if (\Drupal::currentUser()->hasPermission('bulk manage code'))
          {
            if ($form_state['values']['delete_dependency'] == "1")
              {
                //$solution_q = $injected_database->query("SELECT * FROM {lab_migration_solution_dependency} WHERE dependency_id = %d", $form_state['values']['wrapper']['dependency']);
                $query = \Drupal::database()->select('lab_migration_solution_dependency');
                $query->fields('lab_migration_solution_dependency');
                $query->condition('dependency_id', $form_state['values']['dependency']);
                $solution_q = $query->execute();
                if ($solution_data = $solution_q->fetchObject())
                  {
                    \Drupal::messenger()->addError('Cannot delete dependency since it is linked with some solutions');
                  }
                else
                  {
                    if (lab_migration_delete_dependency($form_state['values']['dependency']))
                      {
                        \Drupal::messenger()->addStatus('Dependency deleted');
                        /* email */
                        $email_subject = t('Dependency deleted');
                        $email_body = t('Dependency deleted : .') . $form_state['values']['dependency'];
                        $email_to = \Drupal::config('lab_migration.settings')->get('lab_migration_emails') . ', ' . $user->mail;
                        $param['standard']['subject'] = $email_subject;
                        $param['standard']['body'] = $email_body;
                        if (!drupal_mail('lab_migration', 'standard', $email_to, language_default(), $param, \Drupal::config('lab_migration.settings')->get('lab_migration_from_email'), TRUE))
                            \Drupal::messenger()->addError('Error sending email message.');
                      }
                  }
              }
          }
      }
  }
function _list_of_dependencies()
  {
    $dependencies = array(
        '0' => 'Please select...'
    );
    //$dependency_q = $injected_database->query("SELECT * FROM {lab_migration_dependency_files} ORDER BY filename ASC");
    $query = \Drupal::database()->select('lab_migration_dependency_files');
    $query->fields('lab_migration_dependency_files');
    $query->orderBy('filename', 'ASC');
    $dependency_q = $query->execute();
    while ($dependency_data = $dependency_q->fetchObject())
      {
        $dependencies[$dependency_data->id] = $dependency_data->filename . ' (' . $dependency_data->filepath . ')';
      }
    return $dependencies;
  }
