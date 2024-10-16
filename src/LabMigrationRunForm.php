<?php
namespace Drupal\lab_migration;

class LabMigrationRunForm extends FormBase {

  /**
   * {@inheritdoc}
   */
  public function getFormId() {
    return 'lab_migration_run_form';
  }

  public function buildForm(array $form, \Drupal\Core\Form\FormStateInterface $form_state) {
    $options_first = _list_of_labs();
    $options_two = _ajax_get_experiment_list();
    $select_two = !$form_state->getValue(['lab_experiment_list']) ? $form_state->getValue(['lab_experiment_list']) : key($options_two);
    $url_lab_id = (int) arg(2);
    if (!$url_lab_id) {
      $selected = !$form_state->getValue(['lab']) ? $form_state->getValue(['lab']) : key($options_first);
    }
    elseif ($url_lab_id == '') {
      $selected = 0;
    }
    else {
      $selected = $url_lab_id;
      ;
    }
    $form = [];
    $form['lab'] = [
      '#type' => 'select',
      '#title' => t('Title of the lab'),
      '#options' => _list_of_labs(),
      '#default_value' => $selected,
      '#ajax' => [
        'callback' => 'ajax_experiment_list_callback'
        ],
    ];
    if (!$url_lab_id) {
      $form['selected_lab'] = [
        '#type' => 'item',
        '#markup' => '<div id="ajax_selected_lab"></div>',
      ];
      $form['selected_lab_r'] = [
        '#type' => 'item',
        '#markup' => '<div id="ajax_selected_lab_r"></div>',
      ];
      $form['selected_lab_pdf'] = [
        '#type' => 'item',
        '#markup' => '<div id="ajax_selected_lab_pdf"></div>',
      ];
      $form['lab_details'] = [
        '#type' => 'item',
        '#markup' => '<div id="ajax_lab_details"></div>',
      ];
      $form['lab_experiment_list'] = [
        '#type' => 'select',
        '#title' => t('Titile of the experiment'),
        '#options' => _ajax_get_experiment_list($selected),
        //'#default_value' => isset($form_state['values']['lab_experiment_list']) ? $form_state['values']['lab_experiment_list'] : '',
            '#ajax' => [
          'callback' => 'ajax_solution_list_callback'
          ],
        '#prefix' => '<div id="ajax_selected_experiment">',
        '#suffix' => '</div>',
        '#states' => [
          'invisible' => [
            ':input[name="lab"]' => [
              'value' => 0
              ]
            ]
          ],
      ];
      $form['download_experiment'] = [
        '#type' => 'item',
        '#markup' => '<div id="ajax_download_experiments"></div>',
      ];
      $form['lab_solution_list'] = [
        '#type' => 'select',
        '#title' => t('Solution'),
        '#options' => _ajax_get_solution_list($select_two),
        //'#default_value' => isset($form_state['values']['lab_solution_list']) ? 
        //$form_state['values']['lab_solution_list'] : '',
            '#ajax' => [
          'callback' => 'ajax_solution_files_callback'
          ],
        '#prefix' => '<div id="ajax_selected_solution">',
        '#suffix' => '</div>',
        '#states' => [
          'invisible' => [
            ':input[name="lab"]' => [
              'value' => 0
              ]
            ]
          ],
      ];
      $form['download_solution'] = [
        '#type' => 'item',
        '#markup' => '<div id="ajax_download_experiment_solution"></div>',
      ];
      $form['edit_solution'] = [
        '#type' => 'item',
        '#markup' => '<div id="ajax_edit_experiment_solution"></div>',
      ];
      $form['solution_files'] = [
        '#type' => 'item',
        //  '#title' => t('List of solution_files'),
            '#markup' => '<div id="ajax_solution_files"></div>',
        '#states' => [
          'invisible' => [
            ':input[name="lab"]' => [
              'value' => 0
              ]
            ]
          ],
      ];
    }
    else {
      $lab_default_value = $url_lab_id;
      $form['selected_lab'] = [
        '#type' => 'item',
        '#markup' => '<div id="ajax_selected_lab">' .  Link::fromTextAndUrl('Download Lab Solutions', 'lab-migration/download/lab/' . $lab_default_value) . '</div>',
      ];
      /* $form['selected_lab_pdf'] = array(
        '#type' => 'item',
        '#markup' => '<div id="ajax_selected_lab_pdf">'. Link::fromTextAndUrl('Download PDF of Lab Solutions', 'lab-migration/generate-lab/' . $lab_default_value . '/1') .'</div>',
        
        );*/
      /*if ($lab_default_value == '2')
          {
            $form['selected_lab_r'] = array(
                '#type' => 'item',
                '#markup' => '<div id="ajax_selected_lab_r">' .  Link::fromTextAndUrl('Download Lab Solutions (r Version)', 'lab-migration-uploads/r_Version.zip') . '</div>'
            );
          }*/
      $form['lab_details'] = [
        '#type' => 'item',
        '#markup' => '<div id="ajax_lab_details">' . _lab_details($lab_default_value) . '</div>',
      ];
      $form['lab_experiment_list'] = [
        '#type' => 'select',
        '#title' => t('Titile of the experiment'),
        '#options' => _ajax_get_experiment_list($selected),
        // '#default_value' => isset($form_state['values']['lab_experiment_list']) ? $form_state['values']['lab_experiment_list'] : '',
            '#ajax' => [
          'callback' => 'ajax_solution_list_callback'
          ],
        '#prefix' => '<div id="ajax_selected_experiment">',
        '#suffix' => '</div>',
        '#states' => [
          'invisible' => [
            ':input[name="lab"]' => [
              'value' => 0
              ]
            ]
          ],
      ];
      $form['download_experiment'] = [
        '#type' => 'item',
        '#markup' => '<div id="ajax_download_experiments"></div>',
      ];
      $form['lab_solution_list'] = [
        '#type' => 'select',
        '#title' => t('Solution'),
        '#options' => _ajax_get_solution_list($select_two),
        '#default_value' => !$form_state->getValue(['lab_solution_list']) ? $form_state->getValue(['lab_solution_list']) : '',
        '#ajax' => [
          'callback' => 'ajax_solution_files_callback'
          ],
        '#prefix' => '<div id="ajax_selected_solution">',
        '#suffix' => '</div>',
        '#states' => [
          'invisible' => [
            ':input[name="lab_experiment_list"]' => [
              'value' => 0
              ]
            ]
          ],
      ];
      $form['download_solution'] = [
        '#type' => 'item',
        '#markup' => '<div id="ajax_download_experiment_solution"></div>',
      ];
      $form['edit_solution'] = [
        '#type' => 'item',
        '#markup' => '<div id="ajax_edit_experiment_solution"></div>',
      ];
      $form['solution_files'] = [
        '#type' => 'item',
        //  '#title' => t('List of solution_files'),
            '#markup' => '<div id="ajax_solution_files"></div>',
        '#states' => [
          'invisible' => [
            ':input[name="lab_experiment_list"]' => [
              'value' => 0
              ]
            ]
          ],
      ];
    }
    /*
    $form['message'] = array(
    '#type' => 'textarea',
    '#title' => t('If Dis-Approved please specify reason for Dis-Approval'),
    '#prefix' => '<div id= "message_submit">',   
    '#states' => array('invisible' => array(':input[name="lab"]' => array('value' => 0,),),), 
    
    );
    
    $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),      
    '#suffix' => '</div>',
    '#states' => array('invisible' => array(':input[name="lab"]' => array('value' => 0,),),),
    
    );*/
    return $form;
  }

}
