<?php
/**
 * Implementation of hook_mai\Drupal\Core\Link.
 */
function lab_migration_mail($key, &$message, $params)
  {
    $user = \Drupal::currentUser();
    $language = $message['language'];
    //$language = user_preferred_language($user);
    switch ($key)
    {
        case 'solution_proposal_approved':
            /* initializing data */
            //$proposal_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE id = %d LIMIT 1", $params['solution_proposal_approved']['proposal_id']);
            $query = \Drupal::database()->select('lab_migration_proposal');
            $query->fields('lab_migration_proposal');
            $query->condition('id', $params['solution_proposal_approved']['proposal_id']);
            $query->range(0, 1);
            $proposal_q = $query->execute();
            $proposal_data = $proposal_q->fetchObject();
            if ($proposal_data->solution_display == 1)
              {
                $solution_display = 'Yes';
              }
            else
              {
                $solution_display = 'No';
              }
            // $experiment_q = $injected_database->query("SELECT * FROM {lab_migration_experiment} WHERE proposal_id = %d ORDER BY number", $params['solution_proposal_approved']['proposal_id'], 1);
            $query = \Drupal::database()->select('lab_migration_experiment');
            $query->fields('lab_migration_experiment');
            $query->condition('proposal_id', $params['solution_proposal_approved']['proposal_id']);
            $query->orderBy('number', 'ASC');
            $experiment_q = $query->execute();
            $experiment_list = '
      	';
            while ($experiment_data = $experiment_q->fetchObject())
              {
                $experiment_list .= '<p>' . $experiment_data->number . ') ' . $experiment_data->title . '<br> Description: ' . $experiment_data->description . '<br>';
                $experiment_list .= ' ';
                $experiment_list .= '</p>';
              }
            $user_data = \Drupal::entityTypeManager()->getStorage('user')->load($params['solution_proposal_approved']['user_id']);
            $message['headers'] = $params['solution_proposal_approved']['headers'];
            // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $message['subject'] = t('[!site_name] Lab Migration Solution Proposal Approval', array(
//                 '!site_name' => $config->get('site_name', '')
//             ), array(
//                 'language' => $language->language
//             ));

            // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $message['body'] = array(
//                 0 => t('
// Dear ' . $proposal_data->solution_provider_name . ',
// 
// Congratulations! Your proposal for lab migration with the following details has been
// approved:
// 
// Full Name: ' . $proposal_data->solution_provider_name_title . ' ' . $proposal_data->solution_provider_name . '
// Email: ' . $user_data->mail . '
// Contact No.: ' . $proposal_data->solution_provider_contact_ph . '
// Department/Branch: ' . $proposal_data->solution_provider_department . '
// University/Institute: ' . $proposal_data->solution_provider_university . '
// City: ' . $proposal_data->solution_provider_city . '
// State: ' . $proposal_data->solution_provider_state . '
// 
// List of experiments: ' . $experiment_list . '
// 
// Please ensure that ALL the codes follow guidelines at https://r.fossee.in/lab-migration/lab-migration-guidelines
// 
// Best Wishes,
// 
// !site_name Team
// FOSSEE, IIT Bombay', array(
//                     '!site_name' => $config->get('site_name', ''),
//                     '!user_name' => $user_data->name
//                 ), array(
//                     'language' => $language->language
//                 ))
//             );

            break;
        case 'solution_proposal_disapproved':
            $user_data = \Drupal::entityTypeManager()->getStorage('user')->load($params['solution_proposal_disapproved']['user_id']);
            $proposal_id = $params['solution_proposal_disapproved']['proposal_id'];
            $query = \Drupal::database()->select('lab_migration_proposal');
            $query->fields('lab_migration_proposal');
            $query->condition('id', $proposal_id);
            $query->range(0, 1);
            $proposal_q = $query->execute();
            $proposal_data = $proposal_q->fetchObject();
            
            $query = \Drupal::database()->select('lab_migration_experiment');
            $query->fields('lab_migration_experiment');
            $query->condition('proposal_id', $proposal_id);
            $query->orderBy('number', 'ASC');
            $experiment_q = $query->execute();
            $experiment_list = '
      	';
            while ($experiment_data = $experiment_q->fetchObject())
              {
                $experiment_list .= '<p>' . $experiment_data->number . ') ' . $experiment_data->title . '<br> Description: ' . $experiment_data->description . '<br>';
                $experiment_list .= ' ';
                $experiment_list .= '</p>';
              }
            $message['headers'] = $params['solution_proposal_disapproved']['headers'];
            // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $message['subject'] = t('[!site_name] Lab Migration Solution Disapproval', array(
//                 '!site_name' => $config->get('site_name', '')
//             ), array(
//                 'language' => $language->language
//             ));

            // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $message['body'] = array(
//                 'body' => t('
// Dear ' . $proposal_data->name . ',
// 
// We regret to inform you that your Lab migration solution proposal has been disapproved.
// 
// Title of Lab:' . $proposal_data->lab_title . '
// 
// List of experiments: ' . $experiment_list . '
// 
// Reason: ' . $params['solution_proposal_disapproved']['message'] . '
// 
// You are welcome to submit a new proposal.
// 
// Best Wishes,
// 
// !site_name Team
// FOSSEE, IIT Bombay', array(
//                     '!site_name' => $config->get('site_name', ''),
//                     '!user_name' => $user_data->name
//                 ), array(
//                     'language' => $language->language
//                 ))
//             );

            break;
        case 'proposal_received':
            /* initializing data */
            // $proposal_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE id = %d LIMIT 1", $params['proposal_received']['proposal_id']);
            // $proposal_data = $proposal_q->fetchObject();
            $query = \Drupal::database()->select('lab_migration_proposal');
            $query->fields('lab_migration_proposal');
            $query->condition('id', $params['proposal_received']['proposal_id']);
            $query->range(0, 1);
            $proposal_data = $query->execute()->fetchObject();
            /* $samplecodefilename = "";
            if (strlen($proposal_data->samplefilepath) >= 5)
            {
            $samplecodefilename = substr($proposal_data->samplefilepath, strrpos($proposal_data->samplefilepath, '/') + 1);
            }
            else
            {
            $samplecodefilename = "Not provided";
            }*/
            if ($proposal_data->solution_display == 1)
              {
                $solution_display = 'Yes';
              }
            else
              {
                $solution_display = 'No';
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
                $solution_provider_user = 'Unknown';
              }
            // $experiment_q = $injected_database->query("SELECT * FROM {lab_migration_experiment} WHERE proposal_id = %d ORDER BY number",
            //  $params['proposal_received']['proposal_id'], 1);
            $query = \Drupal::database()->select('lab_migration_experiment');
            $query->fields('lab_migration_experiment');
            $query->condition('proposal_id', $params['proposal_received']['proposal_id']);
            $query->orderBy('number', 'ASC');
            $experiment_q = $query->execute();
            $experiment_list = '
      	';
            while ($experiment_data = $experiment_q->fetchObject())
              {
                $experiment_list .= '<p>' . $experiment_data->number . ') ' . $experiment_data->title . '<br> Description: ' . $experiment_data->description . '<br>';
                $experiment_list .= ' ';
                $experiment_list .= '</p>';
              }
            $user_data = \Drupal::entityTypeManager()->getStorage('user')->load($params['proposal_received']['user_id']);
            $message['headers'] = $params['proposal_received']['headers'];
            // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $message['subject'] = t('[!site_name] Your Lab migration proposal has been received', array(
//                 '!site_name' => $config->get('site_name', '')
//             ), array(
//                 'language' => $language->language
//             ));

            // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $message['body'] = array(
//                 'body' => t('
// Dear ' . $proposal_data->name . ',
// 
// We have received your proposal for lab migration with the following details:
// 
// Full Name: ' . $proposal_data->name_title . ' ' . $proposal_data->name . '
// Email: ' . $user_data->mail . '
// Contact No.: ' . $proposal_data->contact_ph . '
// Department/Branch: ' . $proposal_data->department . '
// University/Institute: ' . $proposal_data->university . '
// City: ' . $proposal_data->city . '
// State: ' . $proposal_data->state . '
// 
// 
// Solution Provided By: ' . $solution_provider_user . '
// 
// List of experiments: ' . $experiment_list . '
// 
// The proposal is under review. You will be notified of the decision.
// 
// Best Wishes,
// 
// !site_name Team
// FOSSEE, IIT Bombay', array(
//                     '!site_name' => $config->get('site_name', ''),
//                     '!user_name' => $user_data->name
//                 ), array(
//                     'language' => $language->language
//                 ))
//             );

            break;
        case 'proposal_disapproved':
            /* initializing data */
            // $proposal_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE id = %d LIMIT 1", $params['proposal_disapproved']['proposal_id']);
            //$proposal_data = $proposal_q->fetchObject();
            $query = \Drupal::database()->select('lab_migration_proposal');
            $query->fields('lab_migration_proposal');
            $query->condition('id', $params['proposal_disapproved']['proposal_id']);
            $query->range(0, 1);
            $proposal_data = $query->execute()->fetchObject();
            $samplecodefilename = "";
            if (strlen($proposal_data->samplefilepath) >= 5)
              {
                $samplecodefilename = substr($proposal_data->samplefilepath, strrpos($proposal_data->samplefilepath, '/') + 1);
              }
            else
              {
                $samplecodefilename = "Not provided";
              }
            if ($proposal_data->solution_display == 1)
              {
                $solution_display = 'Yes';
              }
            else
              {
                $solution_display = 'No';
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
                $solution_provider_user = 'Unknown';
              }
            // $experiment_q = $injected_database->query("SELECT * FROM {lab_migration_experiment} WHERE proposal_id = %d ORDER BY number", $params['proposal_disapproved']['proposal_id'], 1);
            $query = \Drupal::database()->select('lab_migration_experiment');
            $query->fields('lab_migration_experiment');
            $query->condition('proposal_id', $params['proposal_disapproved']['proposal_id']);
            $query->orderBy('number', 'ASC');
            $experiment_q = $query->execute();
            $experiment_list = '
      	';
            while ($experiment_data = $experiment_q->fetchObject())
              {
                $experiment_list .= '<p>' . $experiment_data->number . ') ' . $experiment_data->title . '<br> Description: ' . $experiment_data->description . '<br>';
                $experiment_list .= ' ';
                $experiment_list .= '</p>';
              }
            $user_data = \Drupal::entityTypeManager()->getStorage('user')->load($params['proposal_disapproved']['user_id']);
            $message['headers'] = $params['proposal_disapproved']['headers'];
            // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $message['subject'] = t('[!site_name] Your Lab migration proposal has been disapproved', array(
//                 '!site_name' => $config->get('site_name', '')
//             ), array(
//                 'language' => $language->language
//             ));

            // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $message['body'] = array(
//                 'body' => t('
// Dear ' . $proposal_data->name . ',
// 
// We regret to inform you that your proposal for lab migration with the following details has been disapproved due to the following reason.
// 
// Reason for disapproval: ' . $proposal_data->message . '
// 
// Full Name: ' . $proposal_data->name_title . ' ' . $proposal_data->name . '
// Email: ' . $user_data->mail . '
// Contact No.: ' . $proposal_data->contact_ph . '
// Department/Branch: ' . $proposal_data->department . '
// University/Institute: ' . $proposal_data->university . '
// City: ' . $proposal_data->city . '
// State: ' . $proposal_data->state . '
// 
// Solution Provided By: ' . $solution_provider_user . '
// 
// List of experiments: ' . $experiment_list . '
// 
// Uploaded Sample Code: ' . $samplecodefilename . '
// 
// Please try to re-submit it after incorporating the comments given above. Please note that the records for this proposal have been deleted so that you can submit the proposal again.
// 
// Best Wishes,
// 
// !site_name Team
// FOSSEE, IIT Bombay', array(
//                     '!site_name' => $config->get('site_name', ''),
//                     '!user_name' => $user_data->name
//                 ), array(
//                     'language' => $language->language
//                 ))
//             );

            break;
        case 'proposal_approved':
            /* initializing data */
            // $proposal_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE id = %d LIMIT 1", $params['proposal_approved']['proposal_id']);
            $query = \Drupal::database()->select('lab_migration_proposal');
            $query->fields('lab_migration_proposal');
            $query->condition('id', $params['proposal_approved']['proposal_id']);
            $query->range(0, 1);
            $proposal_q = $query->execute();
            $proposal_data = $proposal_q->fetchObject();
            /* $samplecodefilename = "";
            if (strlen($proposal_data->samplefilepath) >= 5)
            {
            $samplecodefilename = substr($proposal_data->samplefilepath, strrpos($proposal_data->samplefilepath, '/') + 1);
            }
            else
            {
            $samplecodefilename = "Not provided";
            }*/
            if ($proposal_data->solution_display == 1)
              {
                $solution_display = 'Yes';
              }
            else
              {
                $solution_display = 'No';
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
                $solution_provider_user = 'Unknown';
              }
            //$experiment_q = $injected_database->query("SELECT * FROM {lab_migration_experiment} WHERE proposal_id = %d ORDER BY number", $params['proposal_approved']['proposal_id'], 1);
            $query = \Drupal::database()->select('lab_migration_experiment');
            $query->fields('lab_migration_experiment');
            $query->condition('proposal_id', $params['proposal_approved']['proposal_id']);
            $query->orderBy('number', 'ASC');
            $experiment_q = $query->execute();
            $experiment_list = '
      	';
            while ($experiment_data = $experiment_q->fetchObject())
              {
                $experiment_list .= '<p>' . $experiment_data->number . ') ' . $experiment_data->title . '<br> Description: ' . $experiment_data->description . '<br>';
                $experiment_list .= ' ';
                $experiment_list .= '</p>';
              }
            $user_data = \Drupal::entityTypeManager()->getStorage('user')->load($params['proposal_approved']['user_id']);
            $message['headers'] = $params['proposal_approved']['headers'];
            // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $message['subject'] = t('[!site_name] Your Lab migration proposal has been approved', array(
//                 '!site_name' => $config->get('site_name', '')
//             ), array(
//                 'language' => $language->language
//             ));

            // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $message['body'] = array(
//                 0 => t('
// Dear ' . $proposal_data->name . ',
// 
// Congratulations! Your Lab migration proposal with the below details has been approved:
// 
// Full Name: ' . $proposal_data->name_title . ' ' . $proposal_data->name . '
// Email: ' . $user_data->mail . '
// Contact No.: ' . $proposal_data->contact_ph . '
// Department/Branch: ' . $proposal_data->department . '
// University/Institute: ' . $proposal_data->university . '
// City: ' . $proposal_data->city . '
// State: ' . $proposal_data->state . '
// 
// 
// Solution Provided By: ' . $solution_provider_user . '
// 
// List of experiments: ' . $experiment_list . '
// 
// Please ensure that ALL the guidelines for coding are strictly followed:
// https://r.fossee.in/lab-migration/lab-migration-guidelines
// 
// Best Wishes,
// 
// !site_name Team
// FOSSEE, IIT Bombay', array(
//                     '!site_name' => $config->get('site_name', ''),
//                     '!user_name' => $user_data->name
//                 ), array(
//                     'language' => $language->language
//                 ))
//             );

            break;
        case 'proposal_completed':
            /* initializing data */
            //$proposal_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE id = %d LIMIT 1", $params['proposal_completed']['proposal_id']);
            $query = \Drupal::database()->select('lab_migration_proposal');
            $query->fields('lab_migration_proposal');
            $query->condition('id', $params['proposal_completed']['proposal_id']);
            $query->range(0, 1);
            $proposal_q = $query->execute();
            $proposal_data = $proposal_q->fetchObject();
            if ($proposal_data->solution_display == 1)
              {
                $solution_display = 'Yes';
              }
            else
              {
                $solution_display = 'No';
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
                    $solution_provider_user = 'Unknown';
                  }
              }
            //$experiment_q = $injected_database->query("SELECT * FROM {lab_migration_experiment} WHERE proposal_id = %d ORDER BY number", $params['proposal_completed']['proposal_id'], 1);
            $query = \Drupal::database()->select('lab_migration_experiment');
            $query->fields('lab_migration_experiment');
            $query->condition('proposal_id', $params['proposal_completed']['proposal_id']);
            $query->orderBy('number', 'ASC');
            $experiment_q = $query->execute();
            $experiment_list = '
      	';
            while ($experiment_data = $experiment_q->fetchObject())
              {
                $experiment_list .= '<p>' . $experiment_data->number . ') ' . $experiment_data->title . '<br> Description: ' . $experiment_data->description . '<br>';
                $experiment_list .= ' ';
                $experiment_list .= '</p>';
              }
            $user_data = \Drupal::entityTypeManager()->getStorage('user')->load($params['proposal_completed']['user_id']);
            $message['headers'] = $params['proposal_completed']['headers'];
            // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $message['subject'] = t('[!site_name] Congratulations for completion of the Lab migration', array(
//                 '!site_name' => $config->get('site_name', '')
//             ), array(
//                 'language' => $language->language
//             ));

            // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $message['body'] = array(
//                 'body' => t('
// Dear ' . $proposal_data->name . ',
// 
// Following lab migration has been completed successfully:
// 
// Full Name: ' . $proposal_data->name_title . ' ' . $proposal_data->name . '
// Email: ' . $user_data->mail . '
// Contact No.: ' . $proposal_data->contact_ph . '
// Department/Branch: ' . $proposal_data->department . '
// University/Institute: ' . $proposal_data->university . '
// City: ' . $proposal_data->city . '
// State: ' . $proposal_data->state . '
// 
// Solution for this lab has been provided by ' . $solution_provider_user . '
// 
// List of experiments: ' . $experiment_list . '
// 
// Your lab solution is now available at following link to download.
// 
// https://r.fossee.in/lab-migration/lab-migration-run/' . $proposal_data->id . '
// 
// Best Wishes,
// 
// !site_name Team
// FOSSEE, IIT Bombay', array(
//                     '!site_name' => $config->get('site_name', ''),
//                     '!user_name' => $user_data->name
//                 ), array(
//                     'language' => $language->language
//                 ))
//             );

            break;
        case 'solution_proposal_received':
            /* initializing data */
            //$proposal_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE id = %d LIMIT 1", $params['solution_proposal_received']['proposal_id']);
            $query = \Drupal::database()->select('lab_migration_proposal');
            $query->fields('lab_migration_proposal');
            $query->condition('id', $params['solution_proposal_received']['proposal_id']);
            $query->range(0, 1);
            $proposal_q = $query->execute();
            $proposal_data = $proposal_q->fetchObject();
            if ($proposal_data->solution_display == 1)
              {
                $solution_display = 'Yes';
              }
            else
              {
                $solution_display = 'No';
              }
            //$experiment_q = $injected_database->query("SELECT * FROM {lab_migration_experiment} WHERE proposal_id = %d ORDER BY number", $params['solution_proposal_received']['proposal_id'], 1);
            $query = \Drupal::database()->select('lab_migration_experiment');
            $query->fields('lab_migration_experiment');
            $query->condition('proposal_id', $params['solution_proposal_received']['proposal_id']);
            $query->orderBy('number', 'ASC');
            $experiment_q = $query->execute();
            $experiment_list = '
      	';
            while ($experiment_data = $experiment_q->fetchObject())
              {
                $experiment_list .= '<p>' . $experiment_data->number . ') ' . $experiment_data->title . '<br> Description: ' . $experiment_data->description . '<br>';
                $experiment_list .= ' ';
                $experiment_list .= '</p>';
              }
            $user_data = \Drupal::entityTypeManager()->getStorage('user')->load($params['solution_proposal_received']['user_id']);
            $message['headers'] = $params['solution_proposal_received']['headers'];
            // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $message['subject'] = t('[!site_name] Your Lab migration solution proposal has been received', array(
//                 '!site_name' => $config->get('site_name', '')
//             ), array(
//                 'language' => $language->language
//             ));

            // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $message['body'] = array(
//                 'body' => t('
// Dear ' . $proposal_data->solution_provider_name . ',
// 
// We have received your proposal for providing solution for lab migration with the following details:
// 
// List of experiments: ' . $experiment_list . '
// 
// Full Name: ' . $proposal_data->solution_provider_name_title . ' ' . $proposal_data->solution_provider_name . '
// Email: ' . $user->mail . '
// Contact No.: ' . $proposal_data->solution_provider_contact_ph . '
// Department/Branch: ' . $proposal_data->department . '
// University/Institute: ' . $proposal_data->solution_provider_university . '
// 
// 
// Your proposal is under review. You will soon receive an email when the same has been approved / disapproved.
// 
// Please ensure that ALL the codes follow guidelines at https://r.fossee.in/lab-migration/lab-migration-guidelines
// 
// Best Wishes,
// 
// !site_name Team,
// FOSSEE,IIT Bombay', array(
//                     '!site_name' => $config->get('site_name', ''),
//                     '!user_name' => $user_data->name
//                 ), array(
//                     'language' => $language->language
//                 ))
//             );

            break;
        case 'solution_uploaded':
            // $solution_q = $injected_database->query("SELECT * FROM {lab_migration_solution} WHERE id = %d LIMIT 1", $params['solution_uploaded']['solution_id']);
            
            $query = \Drupal::database()->select('lab_migration_solution');
            $query->fields('lab_migration_solution');
            $query->condition('id', $params['solution_uploaded']['solution_id']);
            $query->range(0, 1);
            $solution_q = $query->execute();
            $solution_data = $solution_q->fetchObject();
            $query = \Drupal::database()->select('lab_migration_experiment');
            $query->fields('lab_migration_experiment');
            $query->condition('id', $solution_data->experiment_id);
            $query->range(0, 1);
            $experiment_q = $query->execute();
            $experiment_data = $experiment_q->fetchObject();
            $query = \Drupal::database()->select('lab_migration_proposal');
            $query->fields('lab_migration_proposal');
            $query->condition('id', $experiment_data->proposal_id);
            $query->range(0, 1);
            $proposal_q = $query->execute();
            $proposal_data = $proposal_q->fetchObject();
            $user_data = \Drupal::entityTypeManager()->getStorage('user')->load($params['solution_uploaded']['user_id']);
            // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $message['subject'] = t('[!site_name] You have uploaded Lab migration solution', array(
//                 '!site_name' => $config->get('site_name', '')
//             ), array(
//                 'language' => $language->language
//             ));

            $message['headers'] = $params['solution_uploaded']['headers'];
            // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $message['body'] = array(
//                 'body' => t('
// Dear ' . $proposal_data->solution_provider_name . ',
// 
// You have uploaded the following solution:
// 
// Experiment Title: ' . $experiment_data->title . '
// 
// Solution number: ' . $solution_data->code_number . '
// Caption: ' . $solution_data->caption . '
// 
// The solution is under review. You will be notified of the decision.
// 
// Best Wishes,
// 
// !site_name Team
// FOSSEE, IIT Bombay', array(
//                     '!site_name' => $config->get('site_name', ''),
//                     '!user_name' => $user_data->name
//                 ), array(
//                     'language' => $language->language
//                 ))
//             );

            break;
        case 'solution_approved':
            //$solution_q = $injected_database->query("SELECT * FROM {lab_migration_solution} WHERE id = %d LIMIT 1", $params['solution_approved']['solution_id']);
            $query = \Drupal::database()->select('lab_migration_solution');
            $query->fields('lab_migration_solution');
            $query->condition('id', $params['solution_approved']['solution_id']);
            $query->range(0, 1);
            $solution_q = $query->execute();
            $solution_data = $solution_q->fetchObject();
            $query = \Drupal::database()->select('lab_migration_experiment');
            $query->fields('lab_migration_experiment');
            $query->condition('id', $solution_data->experiment_id);
            $query->range(0, 1);
            $experiment_q = $query->execute();
            $experiment_data = $experiment_q->fetchObject();
            $query = \Drupal::database()->select('lab_migration_proposal');
            $query->fields('lab_migration_proposal');
            $query->condition('id', $experiment_data->proposal_id);
            $query->range(0, 1);
            $proposal_q = $query->execute();
            $proposal_data = $proposal_q->fetchObject();
            $user_data = \Drupal::entityTypeManager()->getStorage('user')->load($params['solution_approved']['user_id']);
            $message['headers'] = $params['solution_approved']['headers'];
            // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $message['subject'] = t('[!site_name] Your uploaded Lab migration solution has been approved', array(
//                 '!site_name' => $config->get('site_name', '')
//             ), array(
//                 'language' => $language->language
//             ));

            // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $message['body'] = array(
//                 'body' => t('
// Dear ' . $proposal_data->solution_provider_name . ',
// 
// Your following solution has been approved:
// 
// Experiment Title: ' . $experiment_data->title . '
// 
// Solution number: ' . $solution_data->code_number . '
// Caption: ' . $solution_data->caption . '
// 
// Please ensure that ALL the codes follow guidelines at https://r.fossee.in/lab-migration/lab-migration-guidelines
// 
// Best Wishes,
// 
// !site_name Team
// FOSSEE, IIT Bombay', array(
//                     '!site_name' => $config->get('site_name', ''),
//                     '!user_name' => $user_data->name
//                 ), array(
//                     'language' => $language->language
//                 ))
//             );

            break;
        case 'solution_disapproved':
            $query = \Drupal::database()->select('lab_migration_proposal');
            $query->fields('lab_migration_proposal');
            $query->condition('id', $params['solution_disapproved']['solution_id']);
            $query->range(0, 1);
            $proposal_q = $query->execute();
            $proposal_data = $proposal_q->fetchObject();
            $user_data = \Drupal::entityTypeManager()->getStorage('user')->load($params['solution_disapproved']['user_id']);
            $message['headers'] = $params['solution_disapproved']['headers'];
            // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $message['subject'] = t('[!site_name] Your uploaded Lab migration solution has been disapproved', array(
//                 '!site_name' => $config->get('site_name', '')
//             ), array(
//                 'language' => $language->language
//             ));

            // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $message['body'] = array(
//                 'body' => t('
// Dear ' . $proposal_data->solution_provider_name . ',
// 
// Your following solution has been disapproved:
// 
// Solution number: ' . $params['solution_disapproved']['solution_number'] . '
// Caption: ' . $params['solution_disapproved']['solution_caption'] . '
// 
// Reason for dis-approval: ' . $params['solution_disapproved']['message'] . '
// 
// 
// Best Wishes,
// 
// !site_name Team
// FOSSEE, IIT Bombay', array(
//                     '!site_name' => $config->get('site_name', ''),
//                     '!user_name' => $user_data->name
//                 ), array(
//                     'language' => $language->language
//                 ))
//             );

            break;
        case 'solution_deleted_user':
            $query = \Drupal::database()->select('lab_migration_proposal');
            $query->fields('lab_migration_proposal');
            $query->condition('id', $params['solution_deleted_user']['solution_id']);
            $query->range(0, 1);
            $proposal_q = $query->execute();
            $proposal_data = $proposal_q->fetchObject();
            $user_data = \Drupal::entityTypeManager()->getStorage('user')->load($params['solution_deleted_user']['user_id']);
            $message['headers'] = $params['solution_deleted_user']['headers'];
            // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $message['subject'] = t('[!site_name] User has deleted pending Lab migration solution', array(
//                 '!site_name' => $config->get('site_name', '')
//             ), array(
//                 'language' => $language->language
//             ));

            // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $message['body'] = array(
//                 'body' => t('
// Dear ' . $proposal_data->solution_provider_name . ',
// 
// Your following pending solution has been deleted:
// 
// Title of the Lab: ' . $params['solution_deleted_user']['lab_title'] . '
// Title of the Experiment: ' . $params['solution_deleted_user']['experiment_title'] . '
// 
// Solution number: ' . $params['solution_deleted_user']['solution_number'] . '
// Caption: ' . $params['solution_deleted_user']['solution_caption'] . '
// 
// 
// Best Wishes,
// 
// !site_name Team
// FOSSEE, IIT Bombay', array(
//                     '!site_name' => $config->get('site_name', ''),
//                     '!user_name' => $user_data->name
//                 ), array(
//                     'language' => $language->language
//                 ))
//             );

            break;
        case 'dependency_uploaded':
            $user_data = \Drupal::entityTypeManager()->getStorage('user')->load($params['dependency_uploaded']['user_id']);
            $dependency_files = implode(',', $params['dependency_uploaded']['dependency_names']);
            $message['headers'] = $params['dependency_uploaded']['headers'];
            // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $message['subject'] = t('[!site_name] You have uploaded dependency file', array(
//                 '!site_name' => $config->get('site_name', '')
//             ), array(
//                 'language' => $language->language
//             ));

            // @FIXME
// // @FIXME
// // This looks like another module's variable. You'll need to rewrite this call
// // to ensure that it uses the correct configuration object.
// $message['body'] = array(
//                 'body' => t('
// Dear !user_name,
// 
// You have uploaded following dependency files:
//     ' . $dependency_files . '
// 
// Please ensure that ALL the codes follow guidelines at https://r.fossee.in/lab-migration/lab-migration-guidelines
// 
// Best Wishes,
// 
// !site_name Team,
// FOSSEE,IIT Bombay', array(
//                     '!site_name' => $config->get('site_name', ''),
//                     '!user_name' => $user_data->name
//                 ), array(
//                     'language' => $language->language
//                 ))
//             );

            break;
        case 'standard':
            $message['subject'] = $params['standard']['subject'];
            $message['body'] = $params['standard']['body'];
            $message['headers'] = $params['standard']['headers'];
            break;
    }
  }
