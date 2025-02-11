<?php
// $Id$
function lab_migration_settings_form($form, $form_state)
  {
    $form['emails'] = array(
        '#type' => 'textfield',
        '#title' => t('(Bcc) Notification emails'),
        '#description' => t('Specify emails id for Bcc option of mail system with comma separated'),
        '#size' => 50,
        '#maxlength' => 255,
        '#required' => TRUE,
        '#default_value' => \Drupal::config('lab_migration.settings')->get('lab_migration_emails')
    );
    $form['cc_emails'] = array(
        '#type' => 'textfield',
        '#title' => t('(Cc) Notification emails'),
        '#description' => t('Specify emails id for Cc option of mail system with comma separated'),
        '#size' => 50,
        '#maxlength' => 255,
        '#required' => TRUE,
        '#default_value' => \Drupal::config('lab_migration.settings')->get('lab_migration_cc_emails')
    );
    $form['from_email'] = array(
        '#type' => 'textfield',
        '#title' => t('Outgoing from email address'),
        '#description' => t('Email address to be display in the from field of all outgoing messages'),
        '#size' => 50,
        '#maxlength' => 255,
        '#required' => TRUE,
        '#default_value' => \Drupal::config('lab_migration.settings')->get('lab_migration_from_email')
    );
    $form['extensions']['source'] = array(
        '#type' => 'textfield',
        '#title' => t('Allowed source file extensions'),
        '#description' => t('A comma separated list WITHOUT SPACE of source file extensions that are permitted to be uploaded on the server'),
        '#size' => 50,
        '#maxlength' => 255,
        '#required' => TRUE,
        '#default_value' => \Drupal::config('lab_migration.settings')->get('lab_migration_source_extensions')
    );
    $form['extensions']['dependency'] = array(
        '#type' => 'textfield',
        '#title' => t('Allowed dependency file extensions'),
        '#description' => t('A comma separated list WITHOUT SPACE of dependency file extensions that are permitted to be uploaded on the server'),
        '#size' => 50,
        '#maxlength' => 255,
        '#required' => TRUE,
        '#default_value' => \Drupal::config('lab_migration.settings')->get('lab_migration_dependency_extensions')
    );
    $form['extensions']['result'] = array(
        '#type' => 'textfield',
        '#title' => t('Allowed result file extensions'),
        '#description' => t('A comma separated list WITHOUT SPACE of result file extensions that are permitted to be uploaded on the server'),
        '#size' => 50,
        '#maxlength' => 255,
        '#required' => TRUE,
        '#default_value' => \Drupal::config('lab_migration.settings')->get('lab_migration_result_extensions')
    );
    $form['extensions']['xcos'] = array(
        '#type' => 'textfield',
        '#title' => t('Allowed xcos file extensions'),
        '#description' => t('A comma separated list WITHOUT SPACE of xcos file extensions that are permitted to be uploaded on the server'),
        '#size' => 50,
        '#maxlength' => 255,
        '#required' => TRUE,
        '#default_value' => \Drupal::config('lab_migration.settings')->get('lab_migration_xcos_extensions')
    );
    $form['extensions']['pdf'] = array(
        '#type' => 'textfield',
        '#title' => t('Allowed pdf file extensions'),
        '#description' => t('A comma separated list WITHOUT SPACE of pdf file extensions that are permitted to be uploaded on the server'),
        '#size' => 50,
        '#maxlength' => 255,
        '#required' => TRUE,
        '#default_value' => \Drupal::config('lab_migration.settings')->get('lab_migration_pdf_extensions')
    );
    $form['extensions']['syllabus'] = array(
        '#type' => 'textfield',
        '#title' => t('Allowed syllabus file extensions'),
        '#description' => t('A comma separated list WITHOUT SPACE of xcos file extensions that are permitted to be uploaded on the server'),
        '#size' => 50,
        '#maxlength' => 255,
        '#required' => TRUE,
        '#default_value' => \Drupal::config('lab_migration.settings')->get('lab_migration_syllabus_file_extensions')
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit')
    );
    return $form;
  }
function lab_migration_settings_form_validate($form, &$form_state)
  {
    return;
  }
function lab_migration_settings_form_submit($form, &$form_state)
  {
    \Drupal::configFactory()->getEditable('lab_migration.settings')->set('lab_migration_emails', $form_state['values']['emails'])->save();
    \Drupal::configFactory()->getEditable('lab_migration.settings')->set('lab_migration_cc_emails', $form_state['values']['cc_emails'])->save();
    \Drupal::configFactory()->getEditable('lab_migration.settings')->set('lab_migration_from_email', $form_state['values']['from_email'])->save();
    \Drupal::configFactory()->getEditable('lab_migration.settings')->set('lab_migration_source_extensions', $form_state['values']['source'])->save();
    \Drupal::configFactory()->getEditable('lab_migration.settings')->set('lab_migration_dependency_extensions', $form_state['values']['dependency'])->save();
    \Drupal::configFactory()->getEditable('lab_migration.settings')->set('lab_migration_result_extensions', $form_state['values']['result'])->save();
    \Drupal::configFactory()->getEditable('lab_migration.settings')->set('lab_migration_xcos_extensions', $form_state['values']['xcos'])->save();
    \Drupal::configFactory()->getEditable('lab_migration.settings')->set('lab_migration_pdf_extensions', $form_state['values']['pdf'])->save();
    \Drupal::configFactory()->getEditable('lab_migration.settings')->set('lab_migration_syllabus_file_extensions', $form_state['values']['syllabus'])->save();
    \Drupal::messenger()->addStatus(t('Settings updated'));
  }
