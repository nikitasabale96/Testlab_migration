<?php

/**
 * @file
 * Contains \Drupal\lab_migration\Form\LabMigrationCategoryEditForm.
 */

namespace Drupal\lab_migration\Form;

use Drupal\Core\Form\FormBase;
use Drupal\Core\Form\FormStateInterface;
use Drupal\Core\Render\Element;

class LabMigrationCategoryEditForm extends FormBase {

  /**
   * {@inheritdoc}
   */
  public function getFormId() {
    return 'lab_migration_category_edit_form';
  }

  public function buildForm(array $form, \Drupal\Core\Form\FormStateInterface $form_state) {
    /* get current proposal */
    $proposal_id = (int) arg(4);
    //$proposal_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE id = %d", $proposal_id);
    $query = $injected_database->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('id', $proposal_id);
    $proposal_q = $query->execute();
    if ($proposal_q) {
      if ($proposal_data = $proposal_q->fetchObject()) {
        /* everything ok */
      }
      else {
        add_message(t('Invalid proposal selected. Please try again.'), 'error');
        RedirectResponse('lab-migration/manage-proposal');
        return;
      }
    }
    else {
      add_message(t('Invalid proposal selected. Please try again.'), 'error');
      RedirectResponse('lab-migration/manage-proposal');
      return;
    }
    $form['name'] = [
      '#type' => 'item',
      '#markup' => Link::fromTextAndUrl($proposal_data->name_title . ' ' . $proposal_data->name, 'user/' . $proposal_data->uid),
      '#title' => t('Name'),
    ];
    $form['email_id'] = [
      '#type' => 'item',
      '#markup' => loadMultiple($proposal_data->uid)->mail,
      '#title' => t('Email'),
    ];
    $form['contact_ph'] = [
      '#type' => 'item',
      '#markup' => $proposal_data->contact_ph,
      '#title' => t('Contact No.'),
    ];
    $form['department'] = [
      '#type' => 'item',
      '#markup' => $proposal_data->department,
      '#title' => t('Department/Branch'),
    ];
    $form['university'] = [
      '#type' => 'item',
      '#markup' => $proposal_data->university,
      '#title' => t('University/Institute'),
    ];
    $form['lab_title'] = [
      '#type' => 'item',
      '#markup' => $proposal_data->lab_title,
      '#title' => t('Title of the Lab'),
    ];
    $form['category'] = [
      '#type' => 'select',
      '#title' => t('Category'),
      '#options' => _lm_list_of_departments(),
      '#required' => TRUE,
      '#default_value' => $proposal_data->category,
    ];
    $form['submit'] = [
      '#type' => 'submit',
      '#value' => t('Submit'),
    ];
    $form['cancel'] = [
      '#type' => 'item',
      '#markup' => Link::fromTextAndUrl(t('Cancel'), 'lab-migration/manage-proposal/category'),
    ];
    return $form;
  }

  public function submitForm(array &$form, \Drupal\Core\Form\FormStateInterface $form_state) {
    /* get current proposal */
    $proposal_id = (int) arg(4);
    //$proposal_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE id = %d", $proposal_id);
    $query = $injected_database->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('id', $proposal_id);
    $proposal_q = $query->execute();
    if ($proposal_q) {
      if ($proposal_data = $proposal_q->fetchObject()) {
        /* everything ok */
      }
      else {
        add_message(t('Invalid proposal selected. Please try again.'), 'error');
        RedirectResponse('lab-migration/manage-proposal');
        return;
      }
    }
    else {
      add_message(t('Invalid proposal selected. Please try again.'), 'error');
      RedirectResponse('lab-migration/manage-proposal');
      return;
    }
    $query = "UPDATE {lab_migration_proposal} SET category = :category WHERE id = :proposal_id";
    $args = [
      ":category" => $form_state->getValue(['category']),
      ":proposal_id" => $proposal_data->id,
    ];
    $result = $injected_database->query($query, $args);
    add_message(t('Proposal Category Updated'), 'status');
    RedirectResponse('lab-migration/manage-proposal/category');
  }

}
?>
