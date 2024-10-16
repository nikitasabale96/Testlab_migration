<?php
// $Id$
function lab_migration_proposal_pending()
  {
    /* get pending proposals to be approved */
    $pending_rows = array();
    //$pending_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE approval_status = 0 ORDER BY id DESC");
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('approval_status', 0);
    $query->orderBy('id', 'DESC');
    $pending_q = $query->execute();
    while ($pending_data = $pending_q->fetchObject())
      {
        // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $pending_rows[$pending_data->id] = array(
//             date('d-m-Y', $pending_data->creation_date),
//             l($pending_data->name, 'user/' . $pending_data->uid),
//             $pending_data->lab_title,
//             $pending_data->department,
//             l('Approve', 'lab-migration/manage-proposal/approve/' . $pending_data->id) . ' | ' . l('Edit', 'lab-migration/manage-proposal/edit/' . $pending_data->id)
//         );

      }
    /* check if there are any pending proposals */
    if (!$pending_rows)
      {
        \Drupal::messenger()->addStatus(t('There are no pending proposals.'));
        return '';
      }
    $pending_header = array(
        'Date of Submission',
        'Name',
        'Title of the Lab',
        'Department',
        'Action'
    );
    //$output = theme_table($pending_header, $pending_rows);
    // @FIXME
// _theme has been renamed to __theme and should NEVER be called directly.
// Calling __theme directly can alter the expected output and potentially
// introduce security issues (see https://www.drupal.org/node/2195739). You
// should use renderable arrays instead.
// 
// 
// @see https://www.drupal.org/node/2195739
// $output = theme('table', array(
//         'header' => $pending_header,
//         'rows' => $pending_rows
//     ));

    return $output;
  }
function lab_migration_proposal_pending_solution()
  {
    /* get pending proposals to be approved */
    $pending_rows = array();
    //$pending_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE approval_status = 1 ORDER BY id DESC");
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('approval_status', 1);
    $query->orderBy('id', 'DESC');
    $pending_q = $query->execute();
    while ($pending_data = $pending_q->fetchObject())
      {
        // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $pending_rows[$pending_data->id] = array(
//             date('d-m-Y', $pending_data->creation_date),
//             date('d-m-Y', $pending_data->approval_date),
//             l($pending_data->name, 'user/' . $pending_data->uid),
//             $pending_data->lab_title,
//             $pending_data->department,
//             l('Status', 'lab-migration/manage-proposal/status/' . $pending_data->id)
//         );

      }
    /* check if there are any pending proposals */
    if (!$pending_rows)
      {
        \Drupal::messenger()->addStatus(t('There are no proposals pending for solutions.'));
        return '';
      }
    $pending_header = array(
        'Date of Submission',
        'Date of Approval',
        'Name',
        'Title of the Lab',
        'Department',
        'Action'
    );
    // @FIXME
// _theme has been renamed to __theme and should NEVER be called directly.
// Calling __theme directly can alter the expected output and potentially
// introduce security issues (see https://www.drupal.org/node/2195739). You
// should use renderable arrays instead.
// 
// 
// @see https://www.drupal.org/node/2195739
// $output = theme('table', array(
//         'header' => $pending_header,
//         'rows' => $pending_rows
//     ));

    return $output;
  }
function lab_migration_proposal()
  {
    /* get pending proposals to be approved */
    $proposal_rows = array();
    //$proposal_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} ORDER BY id DESC");
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->orderBy('id', 'DESC');
    $proposal_q = $query->execute();
    while ($proposal_data = $proposal_q->fetchObject())
      {
        $approval_status = '';
        switch ($proposal_data->approval_status)
        {
            case 0:
                $approval_status = 'Pending';
                break;
            case 1:
                $approval_status = "<span style='color:red;'>Approved</span>";
                break;
            case 2:
                $approval_status = "<span style='color:black;'>Dis-approved</span>";
                break;
            case 3:
                $approval_status = "<span style='color:green;'>Solved</span>";
                break;
            default:
                $approval_status = 'Unknown';
                break;
        }
        // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $proposal_rows[] = array(
//             date('d-m-Y', $proposal_data->creation_date),
//             l($proposal_data->name, 'user/' . $proposal_data->uid),
//             $proposal_data->lab_title,
//             $proposal_data->department,
//             $approval_status,
//             l('Status', 'lab-migration/manage-proposal/status/' . $proposal_data->id) . ' | ' . l('Edit', 'lab-migration/manage-proposal/edit/' . $proposal_data->id)
//         );

      }
    /* check if there are any pending proposals */
    if (!$proposal_rows)
      {
        \Drupal::messenger()->addStatus(t('There are no proposals.'));
        return '';
      }
    $proposal_header = array(
        'Date of Proposal Submission',
        'Name',
        'Title of the Lab',
        'Department',
        'Status',
        'Action'
    );
    // @FIXME
// _theme has been renamed to __theme and should NEVER be called directly.
// Calling __theme directly can alter the expected output and potentially
// introduce security issues (see https://www.drupal.org/node/2195739). You
// should use renderable arrays instead.
// 
// 
// @see https://www.drupal.org/node/2195739
// $output = theme('table', array(
//         'header' => $proposal_header,
//         'rows' => $proposal_rows
//     ));

    return $output;
  }
function lab_migration_category_proposal()
  {
    /* get pending proposals to be approved */
    $proposal_rows = array();
    // $proposal_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} ORDER BY id DESC");
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->orderBy('id', 'DESC');
    $proposal_q = $query->execute();
    while ($proposal_data = $proposal_q->fetchObject())
      {
        // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $proposal_rows[] = array(
//             date('d-m-Y', $proposal_data->creation_date),
//             l($proposal_data->name, 'user/' . $proposal_data->uid),
//             $proposal_data->lab_title,
//             $proposal_data->department,
//             $proposal_data->category,
//             l('Edit Category', 'lab-migration/manage-proposal/category/edit/' . $proposal_data->id)
//         );

      }
    $proposal_header = array(
        'Date of Submission',
        'Name',
        'Title of the Lab',
        'Department',
        'Category',
        'Action'
    );
    // @FIXME
// _theme has been renamed to __theme and should NEVER be called directly.
// Calling __theme directly can alter the expected output and potentially
// introduce security issues (see https://www.drupal.org/node/2195739). You
// should use renderable arrays instead.
// 
// 
// @see https://www.drupal.org/node/2195739
// $output = theme('table', array(
//         'header' => $proposal_header,
//         'rows' => $proposal_rows
//     ));

    return $output;
  }
/******************************************************************************/
/************************** PROPOSAL APPROVAL FORM ****************************/
/******************************************************************************/
function lab_migration_proposal_approval_form($form, $form_state)
  {
    $user = \Drupal::currentUser();
    /* get current proposal */
    $proposal_id = (int) arg(3);
    //$proposal_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE id = %d", $proposal_id);
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('id', $proposal_id);
    $proposal_q = $query->execute();
    if ($proposal_q)
      {
        if ($proposal_data = $proposal_q->fetchObject())
          {
            /* everything ok */
          }
        else
          {
            \Drupal::messenger()->addError(t('Invalid proposal selected. Please try again.'));
            RedirectResponse('lab-migration/manage-proposal');
            return;
          }
      }
    else
      {
        \Drupal::messenger()->addError(t('Invalid proposal selected. Please try again.'));
        RedirectResponse('lab-migration/manage-proposal');
        return;
      }
    // var_dump($proposal_data->name_title);
    //    die;
    // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $form['name'] = array(
//         '#type' => 'item',
//         '#markup' => l($proposal_data->name_title . ' ' . $proposal_data->name, 'user/' . $proposal_data->uid),
//         '#title' => t('Name')
//     );

    $form['email_id'] = array(
        '#type' => 'item',
        '#markup' => \Drupal::entityTypeManager()->getStorage('user')->load($proposal_data->uid)->mail,
        '#title' => t('Email')
    );
    $form['contact_ph'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->contact_ph,
        '#title' => t('Contact No.')
    );
    $form['department'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->department,
        '#title' => t('Department/Branch')
    );
    $form['university'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->university,
        '#title' => t('University/Institute')
    );
    $form['country'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->country,
        '#title' => t('Country')
    );
    $form['all_state'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->state,
        '#title' => t('State')
    );
    $form['city'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->city,
        '#title' => t('City')
    );
    $form['pincode'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->pincode,
        '#title' => t('Pincode/Postal code')
    );
    $form['operating_system'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->operating_system,
        '#title' => t('Operating System')
    );
    $form['version'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->r_version,
        '#title' => t('R Version')
    );
    $form['syllabus_link'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->syllabus_link,
        '#title' => t('Syllabus Link'),
    );
    $form['lab_title'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->lab_title,
        '#title' => t('Title of the Lab')
    );
    /* get experiment details */
    $experiment_list = '<ul>';
    //$experiment_q = $injected_database->query("SELECT * FROM {lab_migration_experiment} WHERE proposal_id = %d ORDER BY id ASC", $proposal_id);
    $query = \Drupal::database()->select('lab_migration_experiment');
    $query->fields('lab_migration_experiment');
    $query->condition('proposal_id', $proposal_id);
    $query->orderBy('id', 'ASC');
    $experiment_q = $query->execute();
    while ($experiment_data = $experiment_q->fetchObject())
      {
        $experiment_list .= '<li>' . $experiment_data->title . '</li>Description of Experiment : ' . $experiment_data->description . '<br>';
      }
    $experiment_list .= '</ul>';
    $form['experiment'] = array(
        '#type' => 'item',
        '#markup' => $experiment_list,
        '#title' => t('Experiments')
    );
    if ($proposal_data->syllabus_copy_file_path != "None")
    {
        // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $form['syllabus_copy_file_path'] = array(
//             '#type' => 'markup',
//             '#markup' => l('Click here to download uploaded syllabus copy', 'lab-migration/download/syllabus-copy-file/' . $proposal_id) . "<br><br>"
//         );

    } //$row->samplefilepath != "None"
    if ($proposal_data->solution_provider_uid == 0)
      {
        $solution_provider = "User will not provide solution, we will have to provide solution";
      }
    else if ($proposal_data->solution_provider_uid == $proposal_data->uid)
      {
        $solution_provider = "Proposer will provide the solution of the lab";
      }
    else
      {
        $solution_provider_user_data = \Drupal::entityTypeManager()->getStorage('user')->load($proposal_data->solution_provider_uid);
        if ($solution_provider_user_data)
        
            // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
$solution_provider = "Solution will be provided by user " . Link::fromTextAndUrl($solution_provider_user_data->name, 'user/' . $proposal_data->solution_provider_uid);
           else
           $solution_provider = "User does not exists";
      }
    
    $form['solution_provider_uid'] = array(
        '#type' => 'item',
        '#title' => t('Do you want to provide the solution'),
        '#markup' => $solution_provider
    );
    /* $form['solution_display'] = array(
    '#type' => 'item',
    '#title' => t('Do you want to display the solution on the www.r.fossee.in website'),
    '#markup' => ($proposal_data->solution_display == 1) ? "Yes" : "No",
    );*/
    $form['approval'] = array(
        '#type' => 'radios',
        '#title' => t('Lab migration proposal'),
        '#options' => array(
            '1' => 'Approve',
            '2' => 'Disapprove'
        ),
        '#required' => TRUE
    );
    $form['message'] = array(
        '#type' => 'textarea',
        '#title' => t('Reason for disapproval'),
        '#attributes' => array(
            'placeholder' => t('Enter reason for disapproval in minimum 30 characters '),
            'cols' => 50,
            'rows' => 4
        ),
        '#states' => array(
            'visible' => array(
                ':input[name="approval"]' => array(
                    'value' => '2'
                )
            )
        )
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit')
    );
    // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $form['cancel'] = array(
//         '#type' => 'item',
//         '#markup' => l(t('Cancel'), 'lab-migration/manage-proposal')
//     );

    return $form;
  }
function lab_migration_proposal_approval_form_validate($form, &$form_state)
  {
    if ($form_state['values']['approval'] == 2)
      {
        if ($form_state['values']['message'] == '')
          {
            $form_state->setErrorByName('message', t('Reason for disapproval could not be empty'));
          }
      }
  }
function lab_migration_proposal_approval_form_submit($form, &$form_state)
  {
    $user = \Drupal::currentUser();
    /* get current proposal */
    $proposal_id = (int) arg(3);
    // $proposal_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE id = %d", $proposal_id);
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('id', $proposal_id);
    $proposal_q = $query->execute();
    if ($proposal_q)
      {
        if ($proposal_data = $proposal_q->fetchObject())
          {
            /* everything ok */
          }
        else
          {
            \Drupal::messenger()->addError(t('Invalid proposal selected. Please try again.'));
            RedirectResponse('lab-migration/manage-proposal');
            return;
          }
      }
    else
      {
        \Drupal::messenger()->addError(t('Invalid proposal selected. Please try again.'));
  RedirectResponse('lab-migration/manage-proposal');
        return;
      }
    if ($form_state['values']['approval'] == 1)
      {
        $query = "UPDATE {lab_migration_proposal} SET approver_uid = :uid, approval_date = :date, approval_status = 1, solution_status = 2 WHERE id = :proposal_id";
        $args = array(
            ":uid" => $user->uid,
            ":date" => time(),
            ":proposal_id" => $proposal_id
        );
        \Drupal::database()->query($query, $args);
        /* sending email */
        $user_data = \Drupal::entityTypeManager()->getStorage('user')->load($proposal_data->uid);
        $email_to = $user_data->mail;
        $from = \Drupal::config('lab_migration.settings')->get('lab_migration_from_email');
        $bcc = $user->mail . ', ' . \Drupal::config('lab_migration.settings')->get('lab_migration_emails');
        $cc = \Drupal::config('lab_migration.settings')->get('lab_migration_cc_emails');
        $param['proposal_approved']['proposal_id'] = $proposal_id;
        $param['proposal_approved']['user_id'] = $proposal_data->uid;
        $param['proposal_approved']['headers'] = array(
            'From' => $from,
            'MIME-Version' => '1.0',
            'Content-Type' => 'text/plain; charset=UTF-8; format=flowed; delsp=yes',
            'Content-Transfer-Encoding' => '8Bit',
            'X-Mailer' => 'Drupal',
            'Cc' => $cc,
            'Bcc' => $bcc
        );
        if (!drupal_mail('lab_migration', 'proposal_approved', $email_to, language_default(), $param, $from, TRUE))
            \Drupal::messenger()->addError('Error sending email message.');
        \Drupal::messenger()->addStatus('Lab migration proposal No. ' . $proposal_id . ' approved. User has been notified of the approval.');
        RedirectResponse('lab-migration/manage-proposal');
        return;
      }
    else if ($form_state['values']['approval'] == 2)
      {
        $query = "UPDATE {lab_migration_proposal} SET approver_uid = :uid, approval_date = :date, approval_status = 2, message = :message, solution_provider_uid = 0, solution_status = 0 WHERE id = :proposal_id";
        $args = array(
            ":uid" => $user->uid,
            ":date" => time(),
            ":message" => $form_state['values']['message'],
            ":proposal_id" => $proposal_id
        );
        $result = \Drupal::database()->query($query, $args);
        /* sending email */
        $user_data = \Drupal::entityTypeManager()->getStorage('user')->load($proposal_data->uid);
        $email_to = $user_data->mail;
        $from = \Drupal::config('lab_migration.settings')->get('lab_migration_from_email');
        $bcc = $user->mail . ', ' . \Drupal::config('lab_migration.settings')->get('lab_migration_emails');
        $cc = \Drupal::config('lab_migration.settings')->get('lab_migration_cc_emails');
        $param['proposal_disapproved']['proposal_id'] = $proposal_id;
        $param['proposal_disapproved']['user_id'] = $proposal_data->uid;
        $param['proposal_disapproved']['headers'] = array(
            'From' => $from,
            'MIME-Version' => '1.0',
            'Content-Type' => 'text/plain; charset=UTF-8; format=flowed; delsp=yes',
            'Content-Transfer-Encoding' => '8Bit',
            'X-Mailer' => 'Drupal',
            'Cc' => $cc,
            'Bcc' => $bcc
        );
        if (!drupal_mail('lab_migration', 'proposal_disapproved', $email_to, language_default(), $param, $from, TRUE))
            \Drupal::messenger()->addError('Error sending email message.');
        \Drupal::messenger()->addError('Lab migration proposal No. ' . $proposal_id . ' dis-approved. User has been notified of the dis-approval.');
        RedirectResponse('lab-migration/manage-proposal');
        return;
      }
  }
/******************************************************************************/
/*************************** PROPOSAL STATUS FORM *****************************/
/******************************************************************************/
function lab_migration_proposal_status_form($form, $form_state)
  {
    $user = \Drupal::currentUser();
    /* get current proposal */
    $proposal_id = (int) arg(3);
    //$proposal_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE id = %d", $proposal_id);
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('id', $proposal_id);
    $proposal_q = $query->execute();
    if ($proposal_q)
      {
        if ($proposal_data = $proposal_q->fetchObject())
          {
            /* everything ok */
          }
        else
          {
            \Drupal::messenger()->addError(t('Invalid proposal selected. Please try again.'));
            RedirectResponse('lab-migration/manage-proposal');
            return;
          }
      }
    else
      {
        \Drupal::messenger()->addError(t('Invalid proposal selected. Please try again.'));
        RedirectResponse('lab-migration/manage-proposal');
        return;
      }
    }
    // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $form['name'] = array(
//         '#type' => 'item',
//         '#markup' => l($proposal_data->name_title . ' ' . $proposal_data->name, 'user/' . $proposal_data->uid),
//         '#title' => t('Name')
//     );

    $form['email_id'] = array(
        '#type' => 'item',
        '#markup' => \Drupal::entityTypeManager()->getStorage('user')->load($proposal_data->uid)->mail,
        '#title' => t('Email')
    );
    $form['contact_ph'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->contact_ph,
        '#title' => t('Contact No.')
    );
    $form['department'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->department,
        '#title' => t('Department/Branch')
    );
    $form['university'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->university,
        '#title' => t('University/Institute')
    );
    $form['country'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->country,
        '#title' => t('Country')
    );
    $form['all_state'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->state,
        '#title' => t('State')
    );
    $form['city'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->city,
        '#title' => t('City')
    );
    $form['pincode'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->pincode,
        '#title' => t('Pincode/Postal code')
    );
    $form['operating_system'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->operating_system,
        '#title' => t('Operating System')
    );
    $form['version'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->r_version,
        '#title' => t('R Version')
    );
    $form['syllabus_link'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->syllabus_link,
        '#title' => t('Syllabus Link'),
    );
    $form['lab_title'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->lab_title,
        '#title' => t('Title of the Lab')
    );
    /* get experiment details */
    $experiment_list = '<ul>';
    //$experiment_q = $injected_database->query("SELECT * FROM {lab_migration_experiment} WHERE proposal_id = %d ORDER BY id ASC", $proposal_id);
    $query = \Drupal::database()->select('lab_migration_experiment');
    $query->fields('lab_migration_experiment');
    $query->condition('proposal_id', $proposal_id);
    $query->orderBy('id', 'ASC');
    $experiment_q = $query->execute();
    while ($experiment_data = $experiment_q->fetchObject())
      {
        $experiment_list .= '<li>' . $experiment_data->title . '</li>Description of Experiment : ' . $experiment_data->description . '<br>';
      }
    $experiment_list .= '</ul>';
    $form['experiment'] = array(
        '#type' => 'item',
        '#markup' => $experiment_list,
        '#title' => t('Experiments')
    );
    if ($proposal_data->solution_provider_uid == 0)
      {
        $solution_provider = "User will not provide solution, we will have to provide solution";
      }
    else if ($proposal_data->solution_provider_uid == $proposal_data->uid)
      {
        $solution_provider = "Proposer will provide the solution of the lab";
      }
    else
      {
        $solution_provider_user_data = \Drupal::entityTypeManager()->getStorage('user')->load($proposal_data->solution_provider_uid);
        if ($solution_provider_user_data)
            // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
$solution_provider = "Solution will be provided by user " . Link::fromTextAndUrl($solution_provider_user_data->name, 'user/' . $proposal_data->solution_provider_uid);

        else
            $solution_provider = "User does not exists";
      
    $form['solution_provider_uid'] = array(
        '#type' => 'item',
        '#title' => t('Who will provide the solution'),
        '#markup' => $solution_provider
    );
    /*$form['solution_display'] = array(
    '#type' => 'item',
    '#title' => t('Display the solution on the www.r.fossee.in website'),
    '#markup' => ($proposal_data->solution_display == 1) ? "Yes" : "No",
    );*/
    $proposal_status = '';
    switch ($proposal_data->approval_status)
    {
        case 0:
            $proposal_status = t('Pending');
            break;
        case 1:
            $proposal_status = t('Approved');
            break;
        case 2:
            $proposal_status = t('Dis-approved');
            break;
        case 3:
            $proposal_status = t('Completed');
            break;
        default:
            $proposal_status = t('Unkown');
            break;
    }
    $form['proposal_status'] = array(
        '#type' => 'item',
        '#markup' => $proposal_status,
        '#title' => t('Proposal Status')
    );
    if($proposal_data->approval_status == 0)
    {
        if($proposal_data->expected_completion_date == 0)
        {
            $form['completion_date'] = array(
            '#type' => 'item',
            '#markup' => 'Expecting date of completion soon',
            '#title' => t('Date of Completion')
            );
        }
        else
        {   
            $form['completion_date'] = array(
            '#type' => 'item',
            '#markup' => date('d-m-Y', $proposal_data->expected_completion_date),
            '#title' => t('Expected date of completion')
            );
        }
    }
    if($proposal_data->approval_status == 1)
    {
        if($proposal_data->expected_completion_date == 0)
        {
            $form['completion_date'] = array(
            '#type' => 'item',
            '#markup' => 'Expecting date of completion soon',
            '#title' => t('Date of Completion')
            );
        }
        else
        {   
            $form['completion_date'] = array(
            '#type' => 'item',
            '#markup' => date('d-m-Y', $proposal_data->expected_completion_date),
            '#title' => t('Date of Completion')
            );
        }
    }
    if ($proposal_data->approval_status == 0)
      {
        // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $form['approve'] = array(
//             '#type' => 'item',
//             '#markup' => l('Click here', 'lab-migration/manage-proposal/approve/' . $proposal_id),
//             '#title' => t('Approve')
//         );

      }
    if ($proposal_data->approval_status == 1)
      {
        $form['completed'] = array(
            '#type' => 'checkbox',
            '#title' => t('Completed'),
            '#description' => t('Check if user has provided all experiment solutions.')
        );
      }
    if ($proposal_data->approval_status == 2)
      {
        $form['message'] = array(
            '#type' => 'item',
            '#markup' => $proposal_data->message,
            '#title' => t('Reason for disapproval')
        );
      }
    //DATE OF COMPLETION
    if($proposal_data->approval_status  == 3)
    {
        $form['completion_date'] = array(
        '#type' => 'item',
        '#markup' => date('d-m-Y', $proposal_data->expected_completion_date),
        '#title' => t('Date of Completion')
        );
    }
    if($proposal_data->approval_status == 2)
    {
        $form['completion_date'] = array(
        '#type' => 'item',
        '#markup' => "Proposal is disapproved",
        '#title' => t('Date of Completion')
        );
    }
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit')
    );
    // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $form['cancel'] = array(
//         '#type' => 'markup',
//         '#markup' => l(t('Cancel'), 'lab-migration/manage-proposal/all')
//     );

    return $form;
  }
function lab_migration_proposal_status_form_submit($form, &$form_state)
  {
    $user = \Drupal::currentUser();
    /* get current proposal */
    $proposal_id = (int) arg(3);
    //$proposal_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE id = %d", $proposal_id);
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('id', $proposal_id);
    $proposal_q = $query->execute();
    if ($proposal_q)
      {
        if ($proposal_data = $proposal_q->fetchObject())
          {
            /* everything ok */
          }
        else
          {
            \Drupal::messenger()->addError(t('Invalid proposal selected. Please try again.'));
            RedirectResponse('lab-migration/manage-proposal');
            return;
          }
      }
    else
      {
        \Drupal::messenger()->addError(t('Invalid proposal selected. Please try again.'));
        RedirectResponse('lab-migration/manage-proposal');
        return;
      }
    /* set the book status to completed */
    if ($form_state['values']['completed'] == 1)
      {
        $up_query = "UPDATE lab_migration_proposal SET approval_status = :approval_status , expected_completion_date = :expected_completion_date WHERE id = :proposal_id";
        $args = array(
            ":approval_status" => '3',
            ":proposal_id" => $proposal_id,
            ":expected_completion_date" => time()
        );
        $result = \Drupal::database()->query($up_query, $args);
        CreateReadmeFileLabMigration($proposal_id);
        if (!$result)
          {
            \Drupal::messenger()->addError('Error in update status');
            return;
          }
        /* sending email */
        $user_data = \Drupal::entityTypeManager()->getStorage('user')->load($proposal_data->uid);
        $email_to = $user_data->mail;
        $from = \Drupal::config('lab_migration.settings')->get('lab_migration_from_email');
        $bcc = $user->mail . ', ' . \Drupal::config('lab_migration.settings')->get('lab_migration_emails');
        $cc = \Drupal::config('lab_migration.settings')->get('lab_migration_cc_emails');
        $param['proposal_completed']['proposal_id'] = $proposal_id;
        $param['proposal_completed']['user_id'] = $proposal_data->uid;
        $param['proposal_completed']['headers'] = array(
            'From' => $from,
            'MIME-Version' => '1.0',
            'Content-Type' => 'text/plain; charset=UTF-8; format=flowed; delsp=yes',
            'Content-Transfer-Encoding' => '8Bit',
            'X-Mailer' => 'Drupal',
            'Cc' => $cc,
            'Bcc' => $bcc
        );
        if (!drupal_mail('lab_migration', 'proposal_completed', $email_to, language_default(), $param, $from, TRUE))
            \Drupal::messenger()->addError('Error sending email message.');
        /*$email_to = $user->mail . ', ' . $config->get('lab_migration_emails', '');;
        if (!drupal_mail('lab_migration', 'proposal_completed', $email_to , language_default(), $param, $config->get('lab_migration_from_email', NULL), TRUE))
        add_message('Error sending email message.', 'error');*/
        \Drupal::messenger()->addStatus('Congratulations! Lab Migration proposal has been marked as completed. User has been notified of the completion.');
      }
    RedirectResponse('lab-migration/manage-proposal');
    return;
  }
/******************************************************************************/
/**************************** PROPOSAL EDIT FORM ******************************/
/******************************************************************************/
function lab_migration_proposal_edit_form($form, $form_state)
  {
    $user = \Drupal::currentUser();
    /* get current proposal */
    $proposal_id = (int) arg(3);
    //$proposal_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE id = %d", $proposal_id);
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('id', $proposal_id);
    $proposal_q = $query->execute();
    if ($proposal_q)
      {
        if ($proposal_data = $proposal_q->fetchObject())
          {
            /* everything ok */
          }
        else
          {
            \Drupal::messenger()->addError(t('Invalid proposal selected. Please try again.'));
            RedirectResponse('lab-migration/manage-proposal');
            return;
          }
      }
    else
      {
        \Drupal::messenger()->addError(t('Invalid proposal selected. Please try again.'));
        RedirectResponse('lab-migration/manage-proposal');
        return;
      }
    $user_data = \Drupal::entityTypeManager()->getStorage('user')->load($proposal_data->uid);
    $form['name_title'] = array(
        '#type' => 'select',
        '#title' => t('Title'),
        '#options' => array(
            'Mr' => 'Mr',
            'Ms' => 'Ms',
            'Mrs' => 'Mrs',
            'Dr' => 'Dr',
            'Prof' => 'Prof'
        ),
        '#required' => TRUE,
        '#default_value' => $proposal_data->name_title
    );
    $form['name'] = array(
        '#type' => 'textfield',
        '#title' => t('Name of the Proposer'),
        '#size' => 30,
        '#maxlength' => 50,
        '#required' => TRUE,
        '#default_value' => $proposal_data->name
    );
    $form['email_id'] = array(
        '#type' => 'item',
        '#title' => t('Email'),
        '#markup' => $user_data->mail
    );
    $form['contact_ph'] = array(
        '#type' => 'textfield',
        '#title' => t('Contact No.'),
        '#size' => 30,
        '#maxlength' => 15,
        '#required' => TRUE,
        '#default_value' => $proposal_data->contact_ph
    );
    $form['department'] = array(
        '#type' => 'select',
        '#title' => t('Department/Branch'),
        '#options' => _lm_list_of_departments(),
        '#required' => TRUE,
        '#default_value' => $proposal_data->department
    );
    $form['university'] = array(
        '#type' => 'textfield',
        '#title' => t('University/Institute'),
        '#size' => 30,
        '#maxlength' => 50,
        '#required' => TRUE,
        '#default_value' => $proposal_data->university
    );
    $form['country'] = array(
        '#type' => 'select',
        '#title' => t('Country'),
        '#options' => array(
            'India' => 'India',
            'Others' => 'Others'
        ),
        '#default_value' => $proposal_data->country,
        '#required' => TRUE,
        '#tree' => TRUE,
        '#validated' => TRUE
    );
    $form['other_country'] = array(
        '#type' => 'textfield',
        '#title' => t('Other than India'),
        '#size' => 100,
        '#default_value' => $proposal_data->country,
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
        '#default_value' => $proposal_data->state,
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
        '#default_value' => $proposal_data->city,
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
        '#default_value' => $proposal_data->state,
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
        '#default_value' => $proposal_data->city,
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
        '#default_value' => $proposal_data->pincode,
        '#attributes' => array(
            'placeholder' => 'Insert pincode of your city/ village....'
        )
    );
    $form['operating_system'] = array(
        '#type' => 'textfield',
        '#default_value' => $proposal_data->operating_system,
        '#title' => t('Operating System')
    );
    $form['version'] = array(
        '#type' => 'select',
        '#title' => t('R Version'),
        '#options' => _lm_list_of_software_version(),
        '#markup' => $proposal_data->r_version
    );
    $form['syllabus_link'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->syllabus_link,
        '#title' => t('Syllabus Link'),
    );
    $form['lab_title'] = array(
        '#type' => 'textfield',
        '#title' => t('Title of the Lab'),
        '#size' => 100,
        '#maxlength' => 255,
        '#required' => TRUE,
        '#default_value' => $proposal_data->lab_title
    );
    /* get experiment details */
    // $experiment_q = $injected_database->query("SELECT * FROM {lab_migration_experiment} WHERE proposal_id = %d ORDER BY id ASC", $proposal_id);
    $query = \Drupal::database()->select('lab_migration_experiment');
    $query->fields('lab_migration_experiment');
    $query->condition('proposal_id', $proposal_id);
    $query->orderBy('id', 'ASC');
    $experiment_q = $query->execute();
    /*$form['lab_experiment'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#tree' => TRUE,
    );*/
    for ($counter = 1; $counter <= 15; $counter++)
      {
        $experiment_title = '';
        $experiment_data = $experiment_q->fetchObject();
        if ($experiment_data)
          {
            $experiment_title = $experiment_data->title;
            $experiment_description = $experiment_data->description;
            /*$form['lab_experiment_']['update'][$experiment_data->id] = array(
            '#type' => 'textfield',
            '#title' => t('Title of the Experiment ') . $counter,
            '#size' => 50,
            '#required' => FALSE,
            
            '#default_value' => $experiment_title,
            );
            $form['lab_experiment']['update1'][$experiment_data->id] = array(
            '#type' => 'textarea',
            
            '#title' => t('Description for Experiment ') . $counter,
            '#default_value' => $experiment_description,
            );*/
            $form['lab_experiment_update' . $experiment_data->id] = array(
                '#type' => 'textfield',
                '#title' => t('Title of the Experiment ') . $counter,
                '#size' => 100,
                '#default_value' => $experiment_title
            );
            $namefield = "lab_experiment_update" . $experiment_data->id;
            $form['lab_experiment_description_update' . $experiment_data->id] = array(
                '#type' => 'textarea',
                '#attributes' => array(
                    'placeholder' => t('Enter Description for your experiment ' . $counter)
                ),
                '#default_value' => $experiment_description,
                '#title' => t('Description for Experiment ') . $counter
            );
          }
        else
          {
            $form['lab_experiment_insert' . $counter] = array(
                '#type' => 'textfield',
                '#title' => t('Title of the Experiment ') . $counter,
                '#size' => 100,
                '#required' => FALSE,
                '#default_value' => $experiment_title
            );
            $namefield = "lab_experiment_insert" . $counter;
            $form['lab_experiment_description_insert' . $counter] = array(
                '#type' => 'textarea',
                '#attributes' => array(
                    'placeholder' => t('Enter Description for your experiment ' . $counter)
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
      }
    if ($proposal_data->solution_provider_uid == 0)
      {
        $solution_provider_user = 'Open';
      }
    else if ($proposal_data->solution_provider_uid == $proposal_data->uid)
      {
        $solution_provider_user = 'Proposer';
      }
    else
      {
        $user_data = \Drupal::entityTypeManager()->getStorage('user')->load($proposal_data->solution_provider_uid);
        if (!$user_data)
          {
            $solution_provider_user = 1;
            \Drupal::messenger()->addError('Solution provider user name is invalid');
          }
        $solution_provider_user = $user_data->name;
      }
    $form['solution_provider_uid'] = array(
        '#type' => 'item',
        '#title' => t('Who will provide the solution'),
        '#markup' => $solution_provider_user
    );
    $form['open_solution'] = array(
        '#type' => 'checkbox',
        '#title' => t('Open the solution for everyone')
    );
    $form['solution_display'] = array(
        '#type' => 'hidden',
        '#title' => t('Do you want to display the solution on the www.r.fossee.in website'),
        '#options' => array(
            '1' => 'Yes'
        ),
        '#required' => TRUE,
        // '#default_value' => ($proposal_data->solution_display == 1) ? "1" : "2",
        '#default_value' => '1'
    );
    $form['delete_proposal'] = array(
        '#type' => 'checkbox',
        '#title' => t('Delete Proposal')
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit')
    );
    // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $form['cancel'] = array(
//         '#type' => 'item',
//         '#markup' => l(t('Cancel'), 'lab-migration/manage-proposal')
//     );

    return $form;
  }
function lab_migration_proposal_edit_form_validate($form, &$form_state)
  {
    $proposal_id = (int) arg(3);
    /* check before delete proposal */
    if ($form_state['values']['delete_proposal'] == 1)
      {
        //$experiment_q = $injected_database->query("SELECT * FROM {lab_migration_experiment} WHERE proposal_id = %d", $proposal_id);
        $query = \Drupal::database()->select('lab_migration_experiment');
        $query->fields('lab_migration_experiment');
        $query->condition('proposal_id', $proposal_id);
        $experiment_q = $query->execute();
        while ($experiment_data = $experiment_q->fetchObject())
          {
            //$solution_q = $injected_database->query("SELECT * FROM {lab_migration_solution} WHERE experiment_id = %d", $experiment_data->id);
            $query = \Drupal::database()->select('lab_migration_solution');
            $query->fields('lab_migration_solution');
            $query->condition('experiment_id', $experiment_data->id);
            $solution_q = $query->execute();
            if ($solution_q->fetchObject())
              {
                $form_state->setErrorByName('', t('Cannot delete proposal since there are solutions already uploaded. Use the "Bulk Manage" interface to delete this proposal'));
              }
          }
      }
    return;
  }
function lab_migration_proposal_edit_form_submit($form, &$form_state)
  {
    $user = \Drupal::currentUser();
    /* get current proposal */
    $proposal_id = (int) arg(3);
    // $proposal_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE id = %d", $proposal_id);
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('id', $proposal_id);
    $proposal_q = $query->execute();
    if ($proposal_q)
      {
        if ($proposal_data = $proposal_q->fetchObject())
          {
            /* everything ok */
          }
        else
          {
            \Drupal::messenger()->addError(t('Invalid proposal selected. Please try again.'));
          RedirectResponse('lab-migration/manage-proposal');
            return;
          }
      }
    else
      {
        \Drupal::messenger()->addError(t('Invalid proposal selected. Please try again.'));
        RedirectResponse('lab-migration/manage-proposal');
        return;
      }
    /* delete proposal */
    if ($form_state['values']['delete_proposal'] == 1)
      {
        //$injected_database->query("DELETE FROM {lab_migration_proposal} WHERE id = %d", $proposal_id);
        $query = \Drupal::database()->delete('lab_migration_proposal');
        $query->condition('id', $proposal_id);
        $num_deleted = $query->execute();
        //$injected_database->query("DELETE FROM {lab_migration_experiment} WHERE proposal_id = %d", $proposal_id);
        $query = \Drupal::database()->delete('lab_migration_experiment');
        $query->condition('proposal_id', $proposal_id);
        $num_deleted = $query->execute();
        \Drupal::messenger()->addStatus(t('Proposal Delete'));
        RedirectResponse('lab-migration/manage-proposal');
        return;
      }
    if ($form_state['values']['open_solution'] == 1)
      {
        // $query = "UPDATE {lab_migration_proposal} SET solution_provider_uid = :solution_provider_uid, solution_status = :solution_status, solution_provider_name_title = '', solution_provider_name = '', solution_provider_contact_ph = '', solution_provider_department = '', solution_provider_university = '' WHERE id = :proposal_id";
        // $args= array(
        //    ":solution_provider_uid" => 0, 
        //    ":solution_status" => 0,
        //    ":proposal_id" => $proposal_id,
        // );
        // $result = $injected_database->query($query, $args);
        $result = \Drupal::database()->update('lab_migration_proposal')->fields(array(
            'solution_provider_uid' => 0,
            'solution_status' => 0,
            'solution_provider_name_title' => '',
            'solution_provider_name' => '',
            'solution_provider_contact_ph' => '',
            'solution_provider_department' => '',
            'solution_provider_university' => ''
        ))->condition('id', $proposal_id)->execute();
        if (!$result)
          {
            \Drupal::messenger()->addError(t('Solution already open for everyone.'));
            return;
          }
      }
    $solution_display = 0;
    if ($form_state['values']['solution_display'] == 1)
      {
        $solution_display = 1;
      }
    else
      {
        $solution_display = 0;
      }
    /* update proposal */
    $v = $form_state['values'];
    //$query = "UPDATE {lab_migration_proposal} SET name_title = :name_title, name = :name, contact_ph = :contact_ph, department = :department, university = :unversity, lab_title = :lab_title, solution_display = :solution_display WHERE id = :id";
    // $args= array(    
    //    ":name_title" => $v['name_title'],
    //    ":name" => $v['name'],
    //    "contact_ph" => $v['contact_ph'],
    //    ":department" => $v['department'],
    //    ":university" => $v['university'],
    //    ":lab_title" => $v['lab_title'],
    //    ":solution_display" => $solution_display,
    //    ":id" => $proposal_id,
    //  );
    
    $lab_title = $v['lab_title'];
    $proposar_name = $v['name_title'] . ' ' . $v['name'];
    $university = $v['university'];
    $directory_names = _lm_dir_name($lab_title, $proposar_name, $university);
    if (LM_RenameDir($proposal_id, $directory_names))
      {
        $directory_name = $directory_names;
      }
    else
      {
        return;
      }
    
    $query = \Drupal::database()->update('lab_migration_proposal')->fields(array(
        'name_title' => $v['name_title'],
        'name' => $v['name'],
        'contact_ph' => $v['contact_ph'],
        'department' => $v['department'],
        'university' => $v['university'],
        'city' => $v['city'],
        'pincode' => $v['pincode'],
        'state' => $v['all_state'],
        ":operating_system" => $v['operating_system'],
        ":r_version" => $form_state['values']['version'],
        'lab_title' => $v['lab_title'],
        'solution_display' => $solution_display,
        'directory_name' => $directory_name
    ))->condition('id', $proposal_id);
    $result1 = $query->execute();
    //$result=$injected_database->query($query, $args);
    /* updating existing experiments */
    $query = \Drupal::database()->select('lab_migration_experiment');
    $query->fields('lab_migration_experiment');
    $query->condition('proposal_id', $proposal_id);
    $query->orderBy('id', 'ASC');
    $experiment_q = $query->execute();
    for ($counter = 1; $counter <= 15; $counter++)
      {
        $experiment_data = $experiment_q->fetchObject();
        if ($experiment_data)
          {
            $experiment_field_name = 'lab_experiment_update' . $experiment_data->id;
            $experiment_description = 'lab_experiment_description_update' . $experiment_data->id;
            if (strlen(trim($form_state['values'][$experiment_field_name])) >= 1)
              {
                $query = "UPDATE {lab_migration_experiment} SET title = :title, description= :description WHERE id = :id";
                $args = array(
                    ":title" => trim($form_state['values'][$experiment_field_name]),
                    ":description" => trim($form_state['values'][$experiment_description]),
                    ":id" => $experiment_data->id
                );
                $result2 = \Drupal::database()->query($query, $args);
                if (!$result2)
                  {
                    \Drupal::messenger()->addError(t('Could not update Title of the Experiment : ') . trim($form_state['values'][$experiment_field_name]));
                  }
              }
            else
              {
                $query = "DELETE FROM {lab_migration_experiment} WHERE id = :id LIMIT 1";
                $args = array(
                    ":id" => $experiment_data->id
                );
                $result3 = \Drupal::database()->query($query, $args);
              }
          }
      }
    /* foreach ($form_state['values']['lab_experiment']['update'] as $update_id => $update_value) {
    if (strlen(trim($update_value)) >= 1) {
    $description= $form_state['values']['lab_experiment_description']['update']; 
    $query = "UPDATE {lab_migration_experiment} SET title = :title and description=:description WHERE id = :id";
    $args = array(
    ":title"=>  trim($update_value),
    ":description"=>trim($description),
    ":id"=> $update_id,
    );
    $result2 = $injected_database->query($query, $args);
    if (!$result2)
    {
    add_message(t('Could not update Title of the Experiment : ') . trim($update_value), 'error');
    }
    } else {
    $query = "DELETE FROM {lab_migration_experiment} WHERE id = :id LIMIT 1";
    $args = array( 
    ":id" => $update_id
    );
    $result3 = $injected_database->query($query, $args);
    }
    }*/
    /* inserting new experiments */
    $query = \Drupal::database()->select('lab_migration_experiment');
    $query->fields('lab_migration_experiment');
    $query->condition('proposal_id', $proposal_id);
    $query->orderBy('number', 'DESC');
    $query->range(0, 1);
    $number_q = $query->execute();
    if ($number_data = $number_q->fetchObject())
      {
        $number = (int) $number_data->number;
        $number++;
      }
    else
      {
        $number = 1;
      }
    for ($counter = 1; $counter <= 15; $counter++)
      {
        $lab_experiment_insert = 'lab_experiment_insert' . $counter;
        $lab_experiment_description_insert = 'lab_experiment_description_insert' . $counter;
        if (strlen(trim(isset($form_state['values'][$lab_experiment_insert]))) >= 1)
          {
            $query = "INSERT INTO {lab_migration_experiment} (proposal_id, number, title, description) VALUES (:proposal_id, :number, :title, :description)";
            $args = array(
                ":proposal_id" => $proposal_id,
                ":number" => $number,
                ":title" => trim($form_state['values'][$lab_experiment_insert]),
                ":description" => trim($form_state['values'][$lab_experiment_description_insert])
            );
            $result4 = \Drupal::database()->query($query, $args);
            if (!$result4)
              {
                \Drupal::messenger()->addError(t('Could not insert Title of the Experiment : ') . trim($form_state['values'][$lab_experiment_insert]));
              }
            else
              {
                $number++;
              }
          }
      }
    /* $query = $injected_database->select('lab_migration_experiment');
    $query->fields('lab_migration_experiment');
    $query->condition('proposal_id', $proposal_id);
    $query->orderBy('number', 'DESC');
    $query->range(0, 1);
    $number_q = $query->execute();
    if ($number_data = $number_q->fetchObject()) {
    $number = (int)$number_data->number;
    $number++;
    } else {
    $number = 1;
    }
    $insertvalue = array($insert_id => $insert_value);
    $lab_experimentinsert = $form_state['values']['lab_experiment']['insert'];
    $lab_exp_descriptioninsert=$form_state['values']['lab_experiment_description']['insert'];
    if (is_array($lab_experimentinsert) || is_object($lab_experimentinsert))
    {  
    foreach ($lab_experimentinsert as $insertvalue) {
    //foreach ($form_state['values']['lab_experiment']['insert'] as $insert_id => $insert_value) {
    if (strlen(trim($insert_value)) >= 1) {
    $query = "INSERT INTO {lab_migration_experiment} (proposal_id, number, title, description) VALUES :proposal_id, :number, :title, :description";
    $args = array(
    ":proposal_id" => $proposal_id, 
    ":number" => $number, 
    ":title" => trim($insert_value),
    ":description"=>""
    );
    $result4 = $injected_database->query($query, $args);
    if (!$result4)
    {
    add_message(t('Could not insert Title of the Experiment : ') . trim($insert_value), 'error');
    } else {
    $number++;
    }
    }
    }
    }*/
    \Drupal::messenger()->addStatus(t('Proposal Updated'));
  }
/******************************************************************************/
/**************************** CATEGORY EDIT FORM ******************************/
/******************************************************************************/
function lab_migration_category_edit_form($form, $form_state)
  {
    /* get current proposal */
    $proposal_id = (int) arg(4);
    //$proposal_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE id = %d", $proposal_id);
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('id', $proposal_id);
    $proposal_q = $query->execute();
    if ($proposal_q)
      {
        if ($proposal_data = $proposal_q->fetchObject())
          {
            /* everything ok */
          }
        else
          {
            \Drupal::messenger()->addError(t('Invalid proposal selected. Please try again.'));
            RedirectResponse('lab-migration/manage-proposal');
            return;
          }
      }
    else
      {
        \Drupal::messenger()->addError(t('Invalid proposal selected. Please try again.'));
        RedirectResponse('lab-migration/manage-proposal');
        return;
      }
    // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $form['name'] = array(
//         '#type' => 'item',
//         '#markup' => l($proposal_data->name_title . ' ' . $proposal_data->name, 'user/' . $proposal_data->uid),
//         '#title' => t('Name')
//     );

    $form['email_id'] = array(
        '#type' => 'item',
        '#markup' => \Drupal::entityTypeManager()->getStorage('user')->load($proposal_data->uid)->mail,
        '#title' => t('Email')
    );
    $form['contact_ph'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->contact_ph,
        '#title' => t('Contact No.')
    );
    $form['department'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->department,
        '#title' => t('Department/Branch')
    );
    $form['university'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->university,
        '#title' => t('University/Institute')
    );
    $form['lab_title'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->lab_title,
        '#title' => t('Title of the Lab')
    );
    $form['category'] = array(
        '#type' => 'select',
        '#title' => t('Category'),
        '#options' => _lm_list_of_departments(),
        '#required' => TRUE,
        '#default_value' => $proposal_data->category
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit')
    );
    // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $form['cancel'] = array(
//         '#type' => 'item',
//         '#markup' => l(t('Cancel'), 'lab-migration/manage-proposal/category')
//     );

    return $form;
  }
function lab_migration_category_edit_form_submit($form, &$form_state)
  {
    /* get current proposal */
    $proposal_id = (int) arg(4);
    //$proposal_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE id = %d", $proposal_id);
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('id', $proposal_id);
    $proposal_q = $query->execute();
    if ($proposal_q)
      {
        if ($proposal_data = $proposal_q->fetchObject())
          {
            /* everything ok */
          }
        else
          {
            \Drupal::messenger()->addError(t('Invalid proposal selected. Please try again.'));
            RedirectResponse('lab-migration/manage-proposal');
            return;
          }
      }
    else
      {
        \Drupal::messenger()->addError(t('Invalid proposal selected. Please try again.'));
        RedirectResponse('lab-migration/manage-proposal');
        return;
      }
    $query = "UPDATE {lab_migration_proposal} SET category = :category WHERE id = :proposal_id";
    $args = array(
        ":category" => $form_state['values']['category'],
        ":proposal_id" => $proposal_data->id
    );
    $result = \Drupal::database()->query($query, $args);
    \Drupal::messenger()->addStatus(t('Proposal Category Updated'));
    RedirectResponse('lab-migration/manage-proposal/category');
  }

function CreateReadmeFileLabMigration($proposal_id)
  {
    $result = \Drupal::database()->query("
                        SELECT * from lab_migration_proposal WHERE id = :proposal_id", array(
        ":proposal_id" => $proposal_id
    ));
    $proposal_data = $result->fetchObject();
    $root_path = lab_migration_path();
    $readme_file = fopen($root_path . $proposal_data->directory_name . "/README.txt", "w") or die("Unable to open file!");
    $txt = "";
    $txt .= "About the lab";
    $txt .= "\n" . "\n";
    $txt .= "Title Of The Lab: " . $proposal_data->lab_title . "\n";
    $txt .= "Proposar Name: " . $proposal_data->name_title . " " . $proposal_data->name . "\n";
    $txt .= "Department: " . $proposal_data->department . "\n";
    $txt .= "University: " . $proposal_data->university . "\n";
    $txt .= "Category: " . $proposal_data->department . "\n\n";
    $txt .= "\n" . "\n";
    $txt .= "Solution provider";
    $txt .= "\n" . "\n";
    $txt .= "Solution Provider Name: " . $proposal_data->solution_provider_name_title . " " . $proposal_data->solution_provider_name . "\n";
    $txt .= "Solution Provider University: " . $proposal_data->solution_provider_university . "\n";
    $txt .= "\n" . "\n";
    $txt .= "Lab Migration Project By FOSSEE, IIT Bombay" . "\n";
    fwrite($readme_file, $txt);
    fclose($readme_file);
    return $txt;
  }
function LM_RenameDir($proposal_id, $dir_name)
  {
    $query = \Drupal::database()->query("SELECT directory_name FROM lab_migration_proposal WHERE id = :proposal_id", array(
        ':proposal_id' => $proposal_id
    ));
    $result = $query->fetchObject();
    $new_directory_name = rename(lab_migration_path() . $result->directory_name, lab_migration_path() . $dir_name) or \Drupal::messenger()->addMessage("Unable to rename folder");
    
    return $new_directory_name;
    
  }
function _lm_dir_name($lab, $name, $university)
  {
    $lab_title = ucname($lab);
    $proposar_name = ucname($name);
    $university_name = ucname($university);
    $dir_name = $lab_title . " " . "by" . " " . $proposar_name . ' ' . $university_name;
    $directory_name = str_replace("__", "_", str_replace(" ", "_", $dir_name));
    return $directory_name;
  }
