<?php
// $Id$
function lab_migration_proposal_open()
  {
    $user = \Drupal::currentUser();
    /* get open proposal list */
    $proposal_rows = array();
    //$proposal_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE approval_status = 1 AND solution_provider_uid = 0");
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('approval_status', 1);
    $query->condition('solution_provider_uid', 0);
    $proposal_q = $query->execute();
    $proposal_q_count = $proposal_q->rowCount();
    if ($proposal_q_count != 0)
     {
    while ($proposal_data = $proposal_q->fetchObject())
      {
        // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $proposal_rows[] = array(
//             l($proposal_data->lab_title, 'lab-migration/show-proposal/' . $proposal_data->id),
//             l('Apply', 'lab-migration/show-proposal/' . $proposal_data->id)
//         );

      }
    $proposal_header = array(
        'Title of the Lab',
        'Actions'
    );
    // @FIXME
// _theme has been renamed to __theme and should NEVER be called directly.
// Calling __theme directly can alter the expected output and potentially
// introduce security issues (see https://www.drupal.org/node/2195739). You
// should use renderable arrays instead.
// 
// 
// @see https://www.drupal.org/node/2195739
// $return_html = theme('table', array(
//         'header' => $proposal_header,
//         'rows' => $proposal_rows
//     ));



   }
 else
{

$return_html = 'No proposals are available';
}
return $return_html;
  }
function lab_migration_solution_proposal_form($form, $form_state)
  {
    $user = \Drupal::currentUser();
    $proposal_id = (int) arg(2);
    //$proposal_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE id = %d", $proposal_id);
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('id', $proposal_id);
    $proposal_q = $query->execute();
    $proposal_data = $proposal_q->fetchObject();
    if (!$proposal_data)
      {
        \Drupal::messenger()->addError("Invalid proposal.");
        RedirectResponse('');
      }
    //var_dump($proposal_data->name); die;
    // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $form['name'] = array(
//         '#type' => 'item',
//         '#markup' => l($proposal_data->name_title . ' ' . $proposal_data->name, 'user/' . $proposal_data->uid),
//         '#title' => t('Proposer Name')
//     );

    $form['lab_title'] = array(
        '#type' => 'item',
        '#markup' => $proposal_data->lab_title,
        '#title' => t('Title of the Lab')
    );
    $experiment_html = '';
    //$experiment_q = $injected_database->query("SELECT * FROM {lab_migration_experiment} WHERE proposal_id = %d", $proposal_id);
    $query = \Drupal::database()->select('lab_migration_experiment');
    $query->fields('lab_migration_experiment');
    $query->condition('proposal_id', $proposal_id);
    $experiment_q = $query->execute();
    while ($experiment_data = $experiment_q->fetchObject())
      {
        $experiment_html .= $experiment_data->title . "<br/>";
      }
    $form['experiment'] = array(
        '#type' => 'item',
        '#markup' => $experiment_html,
        '#title' => t('Experiment List')
    );
    $form['solution_provider_name_title'] = array(
        '#type' => 'select',
        '#title' => t('Title'),
        '#options' => array(
            'Mr' => 'Mr',
            'Ms' => 'Ms',
            'Mrs' => 'Mrs',
            'Dr' => 'Dr',
            'Prof' => 'Prof'
        ),
        '#required' => TRUE
    );
    $form['solution_provider_name'] = array(
        '#type' => 'textfield',
        '#title' => t('Name of the Solution Provider'),
        '#size' => 30,
        '#maxlength' => 50,
        '#required' => TRUE
    );
    $form['solution_provider_email_id'] = array(
        '#type' => 'textfield',
        '#title' => t('Email'),
        '#size' => 30,
        '#value' => $user->mail,
        '#disabled' => TRUE
    );
    $form['solution_provider_contact_ph'] = array(
        '#type' => 'textfield',
        '#title' => t('Contact No.'),
        '#size' => 30,
        '#maxlength' => 15,
        '#required' => TRUE
    );
    $form['solution_provider_department'] = array(
        '#type' => 'select',
        '#title' => t('Department/Branch'),
        '#options' => _list_of_departments(),
        '#required' => TRUE
    );
    $form['solution_provider_university'] = array(
        '#type' => 'textfield',
        '#title' => t('University/Institute'),
        '#size' => 30,
        '#maxlength' => 50,
        '#required' => TRUE
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
        '#required' => False,
        '#attributes' => array(
            'placeholder' => 'Enter pincode....'
        )
    );
    $form['version'] = array(
        '#type' => 'select',
        '#title' => t('Version'),
        '#options' => _list_of_software_version(),
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
                    'value' => 'olderversion'
                )
            )
        )
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Apply for Solution')
    );
    return $form;
  }
function lab_migration_solution_proposal_form_validate($form, &$form_state)
  {
    $user = \Drupal::currentUser();
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
    
    if ($form_state['values']['version'] == 'olderversion')
      {
        if ($form_state['values']['older'] == '')
          {
            $form_state->setErrorByName('older', t('Please provide valid version'));
          }
      }
    return;
    //$solution_provider_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE solution_provider_uid = ".$user->uid." AND approval_status IN (0, 1) AND solution_status IN (0, 1, 2)");
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('solution_provider_uid', $user->uid);
    $query->condition('approval_status', array(
        0,
        1
    ), 'IN');
    $query->condition('solution_status', array(
        0,
        1,
        2
    ), 'IN');
    $solution_provider_q = $query->execute();
    if ($solution_provider_q->fetchObject())
      {
        $form_state->setErrorByName('', t("You have already applied for a solution. Please compelete that before applying for another solution."));
        RedirectResponse('lab-migration/open-proposal');
      }
  }
function lab_migration_solution_proposal_form_submit($form, &$form_state)
  {
    $user = \Drupal::currentUser();
    $proposal_id = (int) arg(2);
    if ($form_state['values']['version'] == 'olderversion')
      {
        $form_state['values']['version'] = $form_state['values']['older'];
      }
    //$proposal_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE id = %d", $proposal_id);
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('id', $proposal_id);
    $proposal_q = $query->execute();
    $proposal_data = $proposal_q->fetchObject();
    if (!$proposal_data)
      {
        \Drupal::messenger()->addError("Invalid proposal.");
        RedirectResponse('lab-migration/open-proposal');
      }
    if ($proposal_data->solution_provider_uid != 0)
      {
        \Drupal::messenger()->addError("Someone has already applied for solving this Lab.");
        RedirectResponse('lab-migration/open-proposal');
      }
    $query = "UPDATE {lab_migration_proposal} set solution_provider_uid = :uid, solution_status = :solution_status, solution_provider_name_title = :solution_provider_name_title, solution_provider_name = :solution_provider_contact_name, solution_provider_contact_ph = :solution_provider_contact_ph, solution_provider_department = :solution_provider_department, solution_provider_university = :solution_provider_university , solution_provider_city = :solution_provider_city, solution_provider_pincode = :solution_provider_pincode, solution_provider_state = :solution_provider_state,solution_provider_country = :solution_provider_country, r_version = :r_version WHERE id = :proposal_id";
    $args = array(
        ":uid" => $user->uid,
        ":solution_status" => 1,
        ":solution_provider_name_title" => $form_state['values']['solution_provider_name_title'],
        ":solution_provider_contact_name" => $form_state['values']['solution_provider_name'],
        ":solution_provider_contact_ph" => $form_state['values']['solution_provider_contact_ph'],
        ":solution_provider_department" => $form_state['values']['solution_provider_department'],
        ":solution_provider_university" => $form_state['values']['solution_provider_university'],
        ":solution_provider_city" => $form_state['values']['city'],
        ":solution_provider_pincode" => $form_state['values']['pincode'],
        ":solution_provider_state" => $form_state['values']['all_state'],
        ":solution_provider_country" => $form_state['values']['country'],
        ":r_version" => $form_state['values']['version'],
        
        ":proposal_id" => $proposal_id
    );
    
    $result = \Drupal::database()->query($query, $args);
    \Drupal::messenger()->addStatus("We have received your application. We will get back to you soon.");
    /* sending email */
    $email_to = $user->mail;
    $from = \Drupal::config('lab_migration.settings')->get('lab_migration_from_email');
    $bcc = \Drupal::config('lab_migration.settings')->get('lab_migration_emails');
    $cc = \Drupal::config('lab_migration.settings')->get('lab_migration_cc_emails');
    $param['solution_proposal_received']['proposal_id'] = $proposal_id;
    $param['solution_proposal_received']['user_id'] = $user->uid;
    $param['solution_proposal_received']['headers'] = array(
        'From' => $from,
        'MIME-Version' => '1.0',
        'Content-Type' => 'text/plain; charset=UTF-8; format=flowed; delsp=yes',
        'Content-Transfer-Encoding' => '8Bit',
        'X-Mailer' => 'Drupal',
        'Cc' => $cc,
        'Bcc' => $bcc
    );
    if (!drupal_mail('lab_migration', 'solution_proposal_received', $email_to, language_default(), $param, $from, TRUE))
        \Drupal::messenger()->addError('Error sending email message.');
    /* sending email */
    /* $email_to = $config->get('lab_migration_emails', '');
    if (!drupal_mail('lab_migration', 'solution_proposal_received', $email_to , language_default(), $param, $config->get('lab_migration_from_email', NULL), TRUE))
    add_message('Error sending email message.', 'error');*/
    RedirectResponse('lab-migration/open-proposal');
  }
