<?php
// $Id$
/******************************************************************************/
/***************************** BOOK NOTES *************************************/
/******************************************************************************/
function lab_migration_lab_notes_form($form,$form_state)
  {
    $user = \Drupal::currentUser();
    /* get current proposal */
    $proposal_id = (int) arg(3);
    //$proposal_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE id = %d LIMIT 1", $proposal_id);
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('id', $proposal_id);
    $query->range(0, 1);
    $proposal_q = $query->execute();
    $proposal_data = $proposal_q->fetchObject();
    if (!$proposal_data)
      {
        \Drupal::messenger()->addError(t('Invalid lab selected. Please try again.'));
        RedirectResponse('lab-migration/code-approval');
        return;
      }
    /* get current notes */
    $notes = '';
    //$notes_q = $injected_database->query("SELECT * FROM {lab_migration_notes} WHERE proposal_id = %d LIMIT 1", $proposal_id);
    $query = \Drupal::database()->select('lab_migration_notes');
    $query->fields('lab_migration_notes');
    $query->condition('proposal_id', $proposal_id);
    $query->range(0, 1);
    $notes_q = $query->execute();
    if ($notes_q)
      {
        $notes_data = $notes_q->fetchObject();
        $notes = $notes_data->notes;
      }
    $form['lab_details'] = array(
        '#type' => 'item',
        '#value' => '<span style="color: rgb(128, 0, 0);"><strong>About the Lab</strong></span><br />' . '<strong>Proposer:</strong> ' . $proposal_data->name . '<br />' . '<strong>Title of the Lab:</strong> ' . $proposal_data->lab_title . '<br />'
    );
    $form['notes'] = array(
        '#type' => 'textarea',
        '#rows' => 20,
        '#title' => t('Notes for Reviewers'),
        '#default_value' => $notes
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit')
    );
    // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $form['cancel'] = array(
//         '#type' => 'markup',
//         '#value' => l(t('Back'), 'lab-migration/code-approval')
//     );

    return $form;
  }
function lab_migration_lab_notes_form_submit($form, &$form_state)
  {
    $user = \Drupal::currentUser();
    /* get current proposal */
    $proposal_id = (int) arg(3);
    //$proposal_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE id = %d LIMIT 1", $proposal_id);
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('id', $proposal_id);
    $query->range(0, 1);
    $proposal_q = $query->execute();
    $proposal_data = $proposal_q->fetchObject();
    if (!$proposal_data)
      {
        \Drupal::messenger()->addError(t('Invalid lab selected. Please try again.'));
        RedirectResponse('lab-migration/code-approval');
        return;
      }
    /* find existing notes */
    //$notes_q = $injected_database->query("SELECT * FROM {lab_migration_notes} WHERE proposal_id = %d LIMIT 1", $proposal_id);
    $query = \Drupal::database()->select('lab_migration_notes');
    $query->fields('lab_migration_notes');
    $query->condition('proposal_id', $proposal_id);
    $query->range(0, 1);
    $notes_q = $query->execute();
    $notes_data = $notes_q->fetchObject();
    /* add or update notes in database */
    if ($notes_data)
      {
        $query = "UPDATE {lab_migration_notes} SET notes = :notes WHERE id = :notes_id";
        $args = array(
            ":notes" => $form_state['values']['notes'],
            ":notes_id" => $notes_data->id
        );
        \Drupal::database()->query($query, $args);
        \Drupal::messenger()->addStatus('Notes updated successfully.');
      }
    else
      {
        $query = "INSERT INTO {lab_migration_notes} (proposal_id, notes) VALUES (:proposal_id, :notes)";
        $args = array(
            ":proposal_id" => $proposal_id,
            ":notes" => $form_state['values']['notes']
        );
        \Drupal::database()->query($query, $args);
        \Drupal::messenger()->addStatus('Notes added successfully.');
      }
  }
