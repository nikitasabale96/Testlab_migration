<?php
namespace Drupal\lab_migration;

class LabMigrationSettingsForm extends FormBase {

  /**
   * {@inheritdoc}
   */
  public function getFormId() {
    return 'lab_migration_settings_form';
  }

  public function buildForm(array $form, \Drupal\Core\Form\FormStateInterface $form_state) {
    $form['emails'] = [
      '#type' => 'textfield',
      '#title' => t('(Bcc) Notification emails'),
      '#description' => t('Specify emails id for Bcc option of mail system with comma separated'),
      '#size' => 50,
      '#maxlength' => 255,
      '#required' => TRUE,
      '#default_value' => $config->get('lab_migration_emails', ''),
    ];
    $form['cc_emails'] = [
      '#type' => 'textfield',
      '#title' => t('(Cc) Notification emails'),
      '#description' => t('Specify emails id for Cc option of mail system with comma separated'),
      '#size' => 50,
      '#maxlength' => 255,
      '#required' => TRUE,
      '#default_value' => $config->get('lab_migration_cc_emails', ''),
    ];
    $form['from_email'] = [
      '#type' => 'textfield',
      '#title' => t('Outgoing from email address'),
      '#description' => t('Email address to be display in the from field of all outgoing messages'),
      '#size' => 50,
      '#maxlength' => 255,
      '#required' => TRUE,
      '#default_value' => $config->get('lab_migration_from_email', ''),
    ];
    $form['extensions']['source'] = [
      '#type' => 'textfield',
      '#title' => t('Allowed source file extensions'),
      '#description' => t('A comma separated list WITHOUT SPACE of source file extensions that are permitted to be uploaded on the server'),
      '#size' => 50,
      '#maxlength' => 255,
      '#required' => TRUE,
      '#default_value' => $config->get('lab_migration_source_extensions', ''),
    ];
    $form['extensions']['dependency'] = [
      '#type' => 'textfield',
      '#title' => t('Allowed dependency file extensions'),
      '#description' => t('A comma separated list WITHOUT SPACE of dependency file extensions that are permitted to be uploaded on the server'),
      '#size' => 50,
      '#maxlength' => 255,
      '#required' => TRUE,
      '#default_value' => $config->get('lab_migration_dependency_extensions', ''),
    ];
    $form['extensions']['result'] = [
      '#type' => 'textfield',
      '#title' => t('Allowed result file extensions'),
      '#description' => t('A comma separated list WITHOUT SPACE of result file extensions that are permitted to be uploaded on the server'),
      '#size' => 50,
      '#maxlength' => 255,
      '#required' => TRUE,
      '#default_value' => $config->get('lab_migration_result_extensions', ''),
    ];
    $form['extensions']['xcos'] = [
      '#type' => 'textfield',
      '#title' => t('Allowed xcos file extensions'),
      '#description' => t('A comma separated list WITHOUT SPACE of xcos file extensions that are permitted to be uploaded on the server'),
      '#size' => 50,
      '#maxlength' => 255,
      '#required' => TRUE,
      '#default_value' => $config->get('lab_migration_xcos_extensions', ''),
    ];
    $form['extensions']['pdf'] = [
      '#type' => 'textfield',
      '#title' => t('Allowed pdf file extensions'),
      '#description' => t('A comma separated list WITHOUT SPACE of pdf file extensions that are permitted to be uploaded on the server'),
      '#size' => 50,
      '#maxlength' => 255,
      '#required' => TRUE,
      '#default_value' => $config->get('lab_migration_pdf_extensions', ''),
    ];
    $form['extensions']['syllabus'] = [
      '#type' => 'textfield',
      '#title' => t('Allowed syllabus file extensions'),
      '#description' => t('A comma separated list WITHOUT SPACE of xcos file extensions that are permitted to be uploaded on the server'),
      '#size' => 50,
      '#maxlength' => 255,
      '#required' => TRUE,
      '#default_value' => $config->get('lab_migration_syllabus_file_extensions', ''),
    ];
    $form['submit'] = [
      '#type' => 'submit',
      '#value' => t('Submit'),
    ];
    return $form;
  }

  public function validateForm(array &$form, \Drupal\Core\Form\FormStateInterface $form_state) {
    return;
  }

  public function submitForm(array &$form, \Drupal\Core\Form\FormStateInterface $form_state) {
    $config->set('lab_migration_emails', $form_state->getValue(['emails']));
    $config->set('lab_migration_cc_emails', $form_state->getValue(['cc_emails']));
    $config->set('lab_migration_from_email', $form_state->getValue(['from_email']));
    $config->set('lab_migration_source_extensions', $form_state->getValue(['source']));
    $config->set('lab_migration_dependency_extensions', $form_state->getValue(['dependency']));
    $config->set('lab_migration_result_extensions', $form_state->getValue(['result']));
    $config->set('lab_migration_xcos_extensions', $form_state->getValue(['xcos']));
    $config->set('lab_migration_pdf_extensions', $form_state->getValue(['pdf']));
    $config->set('lab_migration_syllabus_file_extensions', $form_state->getValue(['syllabus']));
    add_message(t('Settings updated'), 'status');
  }

}
