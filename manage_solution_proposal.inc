<?php
// $Id$
function lab_migration_solution_proposal_pending()
  {
    /* get list of solution proposal where the solution_provider_uid is set to some userid except 0 and solution_status is also 1 */
    $pending_rows = array();
    //$pending_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE solution_provider_uid != 0 AND solution_status = 1 ORDER BY id DESC");
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('solution_provider_uid', 0, '!=');
    $query->condition('solution_status', 1);
    $query->orderBy('id', 'DESC');
    $pending_q = $query->execute();
    while ($pending_data = $pending_q->fetchObject())
      {
        // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $pending_rows[$pending_data->id] = array(
//             l($pending_data->name, 'user/' . $pending_data->uid),
//             $pending_data->lab_title,
//             l('Approve', 'lab-migration/manage-proposal/solution-proposal-approve/' . $pending_data->id)
//         );

      }
    /* check if there are any pending proposals */
    if (!$pending_rows)
      {
        \Drupal::messenger()->addStatus(t('There are no pending solution proposals.'));
        return '';
      }
    $pending_header = array(
        'Proposer Name',
        'Title of the Lab',
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
/******************************************************************************/
/***************** SOLUTION PROPOSAL APPROVAL FORM ****************************/
/******************************************************************************/
function lab_migration_solution_proposal_approval_form($form, $form_state)
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
            RedirectResponse('lab-migration/manage-proposal/pending-solution-proposal');
            return;
          }
      }
    else
      {
        \Drupal::messenger()->addError(t('Invalid proposal selected. Please try again.'));
        RedirectResponse('lab-migration/manage-proposal/pending-solution-proposal');
        return;
      }
    // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $form['name'] = array(
//     '#type' => 'item',
//     '#markup' => l($proposal_data->solution_provider_name_title . ' ' . $proposal_data->solution_provider_name, 'user/' . $proposal_data->solution_provider_uid),
//     '#title' => t('Solution Provider Name'),
//   );

  $form['email_id'] = array(
    '#type' => 'item',
    '#markup' => \Drupal::entityTypeManager()->getStorage('user')->load($proposal_data->solution_provider_uid)->mail,
    '#title' => t('Solution Provider Email'),
  );
  $form['contact_ph'] = array(
    '#type' => 'item',
    '#markup' => $proposal_data->solution_provider_contact_ph,
    '#title' => t('Solution Provider Contact No.'),
  );
  $form['department'] = array(
    '#type' => 'item',
    '#markup' => $proposal_data->solution_provider_department,
    '#title' => t('Department/Branch'),
  );
  $form['university'] = array(
    '#type' => 'item',
    '#markup' => $proposal_data->solution_provider_university,
    '#title' => t('University/Institute'),
  );

$form['country'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->solution_provider_country,
        '#title' => t('Country')
    );
    $form['all_state'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->solution_provider_state,
        '#title' => t('State')
    );
    $form['city'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->solution_provider_city,
        '#title' => t('City')
    );
    $form['pincode'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->solution_provider_pincode,
        '#title' => t('Pincode/Postal code')
    );


 $form['esim_version'] = array(
    '#type' => 'item',
    '#title' => t('eSim version used'),
    '#markup'=>$proposal_data->esim_version,
  );


  $form['lab_title'] = array(
    '#type' => 'item',
    '#markup' => $proposal_data->lab_title,
    '#title' => t('Title of the Lab'),
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
        ;
      }
    $experiment_list .= '</ul>';
    $form['experiment'] = array(
        '#type' => 'item',
        '#markup' => $experiment_list,
        '#title' => t('Experiments')
    );
    $form['solution_display'] = array(
        '#type' => 'item',
        '#title' => t('Display the solution on the www.esim.fossee.in website'),
        '#markup' => ($proposal_data->solution_display == 1) ? "Yes" : "No"
    );
    /*if ($proposal_data->solution_provider_uid == 0)
      {
        $solution_provider = "Open";
      }
    else if ($proposal_data->solution_provider_uid == $proposal_data->uid)
      {
        $solution_provider = "Proposer will provide the solution of the lab";
      }
    else
      {
        $solution_provider_user_data = loadMultiple($proposal_data->solution_provider_uid);
        if ($solution_provider_user_data)
          {
            $solution_provider .= '<ul>' . '<li><strong>Solution Provider:</strong> ' . l($solution_provider_user_data->name, 'user/' . $proposal_data->solution_provider_uid) . '</li>' . '<li><strong>Solution Provider Name:</strong> ' . $proposal_data->solution_provider_name_title . ' ' . $proposal_data->solution_provider_name . '</li>' . '<li><strong>Department:</strong> ' . $proposal_data->solution_provider_department . '</li>' . '<li><strong>University:</strong> ' . $proposal_data->solution_provider_university . '</li>' . '</ul>';
          }
        else
          {
            $solution_provider = "User does not exists";
          }
      }*/
      
      // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $proposer .= '<ul>' .
//         '<li><strong>Proposer:</strong> ' . l($proposal_data->name, 'user/' . $proposal_data->uid) . '</li>' .
//         '<li><strong>Proposer Name:</strong> ' . $proposal_data->name_title . ' ' . $proposal_data->name . '</li>' .
// 	'<li><strong>Contact No:</strong> ' . $proposal_data->contact_ph. '</li>' .
// 	'<li><strong>Email:</strong> ' . loadMultiple($proposal_data->uid)->mail . '</li>' .
//         '<li><strong>Department:</strong> ' . $proposal_data->department . '</li>' .
//         '<li><strong>University:</strong> ' . $proposal_data->university . '</li>' .
//         '<li><strong>Country:</strong> ' . $proposal_data->country . '</li>' .
//         '<li><strong>State:</strong> ' . $proposal_data->state . '</li>' .
// 	'<li><strong>City:</strong> ' . $proposal_data->city . '</li>' .
//         '<li><strong>Pincode:</strong> ' . $proposal_data->pincode . '</li>' .
//         '</ul>';

	$form['proposer_details'] = array(
	  '#type' => 'item',
		'#title' => t('Proposer of Lab :'),
		'#markup' => $proposer,
  	);
    /*$form['solution_provider_uid'] = array(
        '#type' => 'item',
        '#title' => t('Solution Provider'),
        '#markup' => $solution_provider
    );*/
    $form['approval'] = array(
        '#type' => 'radios',
        '#title' => t('Solution Provider'),
        '#options' => array(
            '1' => 'Approve',
            '2' => 'Disapprove'
        ),
        '#required' => TRUE
    );
    $form['message'] = array(
        '#type' => 'textarea',
        '#title' => t('Reason for disapproval')
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit')
    );
    // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $form['cancel'] = array(
//         '#type' => 'markup',
//         '#value' => l(t('Cancel'), 'lab-migration/manage-proposal/pending-solution-proposal')
//     );

    return $form;
  }
function lab_migration_solution_proposal_approval_form_validate($form, &$form_state)
  {
    $proposal_id = (int) arg(3);
    // $solution_provider_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE id = %d", $proposal_id);
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('id', $proposal_id);
    $solution_provider_q = $query->execute();
    $solution_provider_data = $solution_provider_q->fetchObject();
    //	$solution_provider_present_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE solution_provider_uid = %d AND approval_status IN (0, 1) AND id != %d", $solution_provider_data->uid, $proposal_id);
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('solution_provider_uid', $solution_provider_data->uid);
    $query->condition('approval_status', array(
        0,
        1
    ), 'IN');
    $query->condition('id', $proposal_id, '<>');
    $solution_provider_present_q = $query->execute();
    if ($x = $solution_provider_present_q->fetchObject())
      {
        \Drupal::messenger()->addMessage($proposal_id);
        $form_state->setErrorByName('', t('Solution provider has already one proposal active'));
      }
  }
function lab_migration_solution_proposal_approval_form_submit($form, &$form_state)
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
            RedirectResponse('lab-migration/manage-proposal/pending-solution-proposal');
            return;
          }
      }
    else
      {
        \Drupal::messenger()->addError(t('Invalid proposal selected. Please try again.'));
        RedirectResponse('lab-migration/manage-proposal/pending-solution-proposal');
        return;
      }
    $user_data = \Drupal::entityTypeManager()->getStorage('user')->load($proposal_data->solution_provider_uid);
    if ($form_state['values']['approval'] == 1)
      {
        $query = "UPDATE {lab_migration_proposal} SET solution_status = 2 WHERE id =:proposal_id";
        $args = array(
            ":proposal_id" => $proposal_id
        );
        \Drupal::database()->query($query, $args);
        /* sending email */
        $email_to = $user_data->mail;
        $from = \Drupal::config('lab_migration.settings')->get('lab_migration_from_email');
        $bcc = $user->mail . ', ' . \Drupal::config('lab_migration.settings')->get('lab_migration_emails');
        $cc = \Drupal::config('lab_migration.settings')->get('lab_migration_cc_emails');
        $param['solution_proposal_approved']['proposal_id'] = $proposal_id;
        $param['solution_proposal_approved']['user_id'] = $proposal_data->solution_provider_uid;
        $param['solution_proposal_approved']['headers'] = array(
            'From' => $from,
            'MIME-Version' => '1.0',
            'Content-Type' => 'text/plain; charset=UTF-8; format=flowed; delsp=yes',
            'Content-Transfer-Encoding' => '8Bit',
            'X-Mailer' => 'Drupal',
            'Cc' => $cc,
            'Bcc' => $bcc
        );
        if (!drupal_mail('lab_migration', 'solution_proposal_approved', $email_to, language_default(), $param, $from, TRUE))
            \Drupal::messenger()->addError('Error sending email message.');
        /*$email_to = $user->mail . ', ' . $config->get('lab_migration_emails', '');
        if (!drupal_mail('lab_migration', 'solution_proposal_approved', $email_to , language_default(), $param, $config->get('lab_migration_from_email', NULL), TRUE))
        add_message('Error sending email message.', 'error');*/
        \Drupal::messenger()->addStatus('Lab migration solution proposal approved. User has been notified of the approval.');
        RedirectResponse('lab-migration/manage-proposal/pending-solution_proposal');
        return;
      }
    else if ($form_state['values']['approval'] == 2)
      {
        $query = "UPDATE {lab_migration_proposal} SET solution_provider_uid = :solution_provider_uid, solution_status = :solution_status, solution_provider_name_title = '', solution_provider_name = '', solution_provider_contact_ph = '', solution_provider_department = '', solution_provider_university = '' WHERE id = :proposal_id";
        $args = array(
            ":solution_provider_uid" => 0,
            ":solution_status" => 0,
            ":proposal_id" => $proposal_id
        );
        \Drupal::database()->query($query, $args);
        /* sending email */
        $email_to = $user_data->mail;
        $from = \Drupal::config('lab_migration.settings')->get('lab_migration_from_email');
        $bcc = $user->mail . ', ' . \Drupal::config('lab_migration.settings')->get('lab_migration_emails');
        $cc = \Drupal::config('lab_migration.settings')->get('lab_migration_cc_emails');
        $param['solution_proposal_disapproved']['proposal_id'] = $proposal_id;
        $param['solution_proposal_disapproved']['user_id'] = $proposal_data->solution_provider_uid;
        $param['solution_proposal_disapproved']['message'] = $form_state['values']['message'];
        $param['solution_proposal_disapproved']['headers'] = array(
            'From' => $from,
            'MIME-Version' => '1.0',
            'Content-Type' => 'text/plain; charset=UTF-8; format=flowed; delsp=yes',
            'Content-Transfer-Encoding' => '8Bit',
            'X-Mailer' => 'Drupal',
            'Cc' => $cc,
            'Bcc' => $bcc
        );
        if (!drupal_mail('lab_migration', 'solution_proposal_disapproved', $email_to, language_default(), $param, $from, TRUE))
            \Drupal::messenger()->addError('Error sending email message.');
        \Drupal::messenger()->addStatus('Lab migration solution proposal dis-approved. User has been notified of the dis-approval.');
        RedirectResponse('lab-migration/manage-proposal/pending-solution-proposal');
        return;
      }
  }
