<?php
// $Id$
function lab_migration_download_solution_file()
  {
    $solution_file_id = arg(3);
    $root_path = lab_migration_path();
    // $solution_files_q = $injected_database->query("SELECT * FROM {lab_migration_solution_files} WHERE id = %d LIMIT 1", $solution_file_id);
    $solution_files_q = \Drupal::database()->query("SELECT lmsf.*, lmp.directory_name FROM lab_migration_solution_files lmsf JOIN lab_migration_solution lms JOIN lab_migration_experiment lme JOIN lab_migration_proposal lmp WHERE lms.id = lmsf.solution_id AND lme.id = lms.experiment_id AND lmp.id = lme.proposal_id AND lmsf.id = :solution_id LIMIT 1", array(':solution_id' => $solution_file_id));
    /*$query = $injected_database->select('lab_migration_solution_files');
    $query->fields('lab_migration_solution_files');
    $query->condition('id', $solution_file_id);
    $query->range(0, 1);
    $solution_files_q = $query->execute();*/
    $solution_file_data = $solution_files_q->fetchObject();
    header('Content-Type: ' . $solution_file_data->filemime);
    header('Content-disposition: attachment; filename="' . str_replace(' ', '_', ($solution_file_data->filename)) . '"');
    header('Content-Length: ' . filesize($root_path . $solution_file_data->directory_name . '/' . $solution_file_data->filepath));
    ob_clean();
    readfile($root_path . $solution_file_data->directory_name . '/' . $solution_file_data->filepath);
  }
function lab_migration_download_dependency_file()
  {
    $dependency_file_id = arg(3);
    $root_path = lab_migration_path();
    //$dependency_file_q = $injected_database->query("SELECT * FROM {lab_migration_dependency_files} WHERE id = %d LIMIT 1", $dependency_file_id);
    $query = \Drupal::database()->select('lab_migration_dependency_files');
    $query->fields('lab_migration_dependency_files');
    $query->condition('id', $dependency_file_id);
    $query->range(0, 1);
    $dependency_files_q = $query->execute();
    $dependency_file_data = $dependency_files_q->fetchObject();
    header('Content-Type: ' . $dependency_file_data->filemime);
    header('Content-disposition: attachment; filename="' . str_replace(' ', '_', ($dependency_file_data->filename)) . '"');
    header('Content-Length: ' . filesize($root_path . $dependency_file_data->filepath));
    ob_clean();
    readfile($root_path . $dependency_file_data->filepath);
  }
function lab_migration_download_solution()
  {
    $solution_id = arg(3);
    $root_path = lab_migration_path();
    /* get solution data */
    //$solution_q = $injected_database->query("SELECT * FROM {lab_migration_solution} WHERE id = %d", $solution_id);
    $query = \Drupal::database()->select('lab_migration_solution');
    $query->fields('lab_migration_solution');
    $query->condition('id', $solution_id);
    $solution_q = $query->execute();
    $solution_data = $solution_q->fetchObject();
    //$experiment_q = $injected_database->query("SELECT * FROM {lab_migration_experiment} WHERE id = %d", $solution_data->experiment_id);
    $query = \Drupal::database()->select('lab_migration_experiment');
    $query->fields('lab_migration_experiment');
    $query->condition('id', $solution_data->experiment_id);
    $experiment_q = $query->execute();
    $experiment_data = $experiment_q->fetchObject();
    //$solution_files_q = $injected_database->query("SELECT * FROM {lab_migration_solution_files} WHERE solution_id = %d", $solution_id);
    /*$query = $injected_database->select('lab_migration_solution_files');
    $query->fields('lab_migration_solution_files');
    $query->condition('solution_id', $solution_id);
    $solution_files_q = $query->execute();*/
    $solution_files_q = \Drupal::database()->query("SELECT lmsf.*, lmp.directory_name FROM lab_migration_solution_files lmsf JOIN lab_migration_solution lms JOIN lab_migration_experiment lme JOIN lab_migration_proposal lmp WHERE lms.id = lmsf.solution_id AND lme.id = lms.experiment_id AND lmp.id = lme.proposal_id AND lmsf.id = :solution_id", array(':solution_id' => $solution_id));
    //$solution_dependency_files_q = $injected_database->query("SELECT * FROM {lab_migration_solution_dependency} WHERE solution_id = %d", $solution_id);
    $query = \Drupal::database()->select('lab_migration_solution_dependency');
    $query->fields('lab_migration_solution_dependency');
    $query->condition('solution_id', $solution_id);
    $solution_dependency_files_q = $query->execute();
    $CODE_PATH = 'CODE' . $solution_data->code_number . '/';
    /* zip filename */
    $zip_filename = $root_path . 'zip-' . time() . '-' . rand(0, 999999) . '.zip';
    /* creating zip archive on the server */
    $zip = new ZipArchive;
    $zip->open($zip_filename, ZipArchive::CREATE);
    while ($solution_files_row = $solution_files_q->fetchObject())
      {
        $zip->addFile($root_path . $solution_files_row->directory_name . '/' . $solution_files_row->filepath, $CODE_PATH . str_replace(' ', '_', ($solution_files_row->filename)));
      }
    /* dependency files */
    while ($solution_dependency_files_row = $solution_dependency_files_q->fetchObject())
      {
        //$dependency_file_data = ($injected_database->query("SELECT * FROM {lab_migration_dependency_files} WHERE id = %d LIMIT 1", $solution_dependency_files_row->dependency_id))->fetchObject();
        $query = \Drupal::database()->select('lab_migration_dependency_files');
        $query->fields('lab_migration_dependency_files');
        $query->condition('id', $solution_dependency_files_row->dependency_id);
        $query->range(0, 1);
        $dependency_file_data = $query->execute()->fetchObject();
        if ($dependency_file_data)
            $zip->addFile($root_path . $dependency_file_data->filepath, $CODE_PATH . 'DEPENDENCIES/' . str_replace(' ', '_', ($dependency_file_data->filename)));
      }
    $zip_file_count = $zip->numFiles;
    $zip->close();
    if ($zip_file_count > 0)
      {
        /* download zip file */
        header('Content-Type: application/zip');
        header('Content-disposition: attachment; filename="CODE' . $solution_data->code_number . '.zip"');
        header('Content-Length: ' . filesize($zip_filename));
        ob_clean();
        //flush();
        readfile($zip_filename);
        unlink($zip_filename);
      }
    else
      {
        \Drupal::messenger()->addError("There are no files in this solutions to download");
        RedirectResponse('lab-migration/lab-migration-run');
      }
  }
function lab_migration_download_experiment()
  {
    $experiment_id = (int)arg(3);
    
    $root_path = lab_migration_path();
    /* get solution data */
    //$experiment_q = $injected_database->query("SELECT * FROM {lab_migration_experiment} WHERE id = %d", $experiment_id);
    $query = \Drupal::database()->select('lab_migration_experiment');
    $query->fields('lab_migration_experiment');
    $query->condition('id', $experiment_id);
    $experiment_q = $query->execute();
    $experiment_data = $experiment_q->fetchObject();
    $EXP_PATH = 'EXP' . $experiment_data->number . '/';
    /* zip filename */
    $zip_filename = $root_path . 'zip-' . time() . '-' . rand(0, 999999) . '.zip';
    /* creating zip archive on the server */
    $zip = new ZipArchive;
    $zip->open($zip_filename, ZipArchive::CREATE);
    //$solution_q = $injected_database->query("SELECT * FROM {lab_migration_solution} WHERE experiment_id = %d AND approval_status = 1", $experiment_id);
    $query = \Drupal::database()->select('lab_migration_solution');
    $query->fields('lab_migration_solution');
    $query->condition('experiment_id', $experiment_id);
    $query->condition('approval_status', 1);
    $solution_q = $query->execute();
    while ($solution_row = $solution_q->fetchObject())
      {
        $CODE_PATH = 'CODE' . $solution_row->code_number . '/';
        // $solution_files_q = $injected_database->query("SELECT * FROM {lab_migration_solution_files} WHERE solution_id = %d", $solution_row->id);
         $solution_files_q = \Drupal::database()->query("SELECT lmsf.*, lmp.directory_name FROM lab_migration_solution_files lmsf JOIN lab_migration_solution lms JOIN lab_migration_experiment lme JOIN lab_migration_proposal lmp WHERE lms.id = lmsf.solution_id AND lme.id = lms.experiment_id AND lmp.id = lme.proposal_id AND lmsf.solution_id = :solution_id", array(':solution_id' => $solution_row->id));
       /* $query = $injected_database->select('lab_migration_solution_files');
        $query->fields('lab_migration_solution_files');
        $query->condition('solution_id', $solution_row->id);
        $solution_files_q = $query->execute();*/
        // $solution_dependency_files_q = $injected_database->query("SELECT * FROM {lab_migration_solution_dependency} WHERE solution_id = %d", $solution_row->id);        
        while ($solution_files_row = $solution_files_q->fetchObject())
          {
            $zip->addFile($root_path . $solution_files_row->directory_name .'/'. $solution_files_row->filepath, $EXP_PATH . $CODE_PATH . str_replace(' ', '_', ($solution_files_row->filename)));
          }
        /* dependency files */
        $query = \Drupal::database()->select('lab_migration_solution_dependency');
        $query->fields('lab_migration_solution_dependency');
        $query->condition('solution_id', $solution_row->id);
        $solution_dependency_files_q = $query->execute();
        while ($solution_dependency_files_row = $solution_dependency_files_q->fetchObject())
          {
            //$dependency_file_data = ($injected_database->query("SELECT * FROM {lab_migration_dependency_files} WHERE id = %d LIMIT 1", $solution_dependency_files_row->dependency_id))->fetchObject();
            $query = \Drupal::database()->select('lab_migration_dependency_files');
            $query->fields('lab_migration_dependency_files');
            $query->condition('id', $solution_dependency_files_row->dependency_id);
            $query->range(0, 1);
            $dependency_file_data = $query->execute()->fetchObject();
            if ($dependency_file_data)
                $zip->addFile($root_path . $dependency_file_data->filepath, $EXP_PATH . $CODE_PATH . 'DEPENDENCIES/' . str_replace(' ', '_', ($dependency_file_data->filename)));
          }
      }
    $zip_file_count = $zip->numFiles;
    $zip->close();
    if ($zip_file_count > 0)
      {
        /* download zip file */
        header('Content-Type: application/zip');
        header('Content-disposition: attachment; filename="EXP' . $experiment_data->number . '.zip"');
        header('Content-Length: ' . filesize($zip_filename));
        ob_clean();
        //flush();
        readfile($zip_filename);
        unlink($zip_filename);
      }
    else
      {
        \Drupal::messenger()->addError("There are no solutions in this experiment to download");
        RedirectResponse('lab-migration/lab-migration-run');
      }
  }
function lab_migration_download_lab()
  {
    $user = \Drupal::currentUser();
    $lab_id = arg(3);
    $root_path = lab_migration_path();
    /* get solution data */
    //$lab_q = $injected_database->query("SELECT * FROM {lab_migration_proposal} WHERE id = %d", $lab_id);
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('id', $lab_id);
    $lab_q = $query->execute();
    $lab_data = $lab_q->fetchObject();
    $LAB_PATH = $lab_data->lab_title . '/';
    /* zip filename */
    $zip_filename = $root_path . 'zip-' . time() . '-' . rand(0, 999999) . '.zip';
    /* creating zip archive on the server */
    $zip = new ZipArchive();
    $zip->open($zip_filename, ZipArchive::CREATE);
    //$experiment_q = $injected_database->query("SELECT * FROM {lab_migration_experiment} WHERE proposal_id = %d", $lab_id);
    $query = \Drupal::database()->select('lab_migration_experiment');
    $query->fields('lab_migration_experiment');
    $query->condition('proposal_id', $lab_id);
    $experiment_q = $query->execute();
    while ($experiment_row = $experiment_q->fetchObject())
      {
        $EXP_PATH = 'EXP' . $experiment_row->number . '/';
        //$solution_q = $injected_database->query("SELECT * FROM {lab_migration_solution} WHERE experiment_id = %d AND approval_status = 1", $experiment_row->id);
        $query = \Drupal::database()->select('lab_migration_solution');
        $query->fields('lab_migration_solution');
        $query->condition('experiment_id', $experiment_row->id);
        $query->condition('approval_status', 1);
        $solution_q = $query->execute();
        while ($solution_row = $solution_q->fetchObject())
          {
            $CODE_PATH = 'CODE' . $solution_row->code_number . '/';
            //$solution_files_q = $injected_database->query("SELECT * FROM {lab_migration_solution_files} WHERE solution_id = %d", $solution_row->id);
            
            $solution_files_q = \Drupal::database()->query("SELECT lmsf.*, lmp.directory_name FROM lab_migration_solution_files lmsf JOIN lab_migration_solution lms JOIN lab_migration_experiment lme JOIN lab_migration_proposal lmp WHERE lms.id = lmsf.solution_id AND lme.id = lms.experiment_id AND lmp.id = lme.proposal_id AND lmsf.id = :solution_id", array(':solution_id' => $solution_row->id));
            /*$query = $injected_database->select('lab_migration_solution_files');
            $query->fields('lab_migration_solution_files');
            $query->condition('solution_id', $solution_row->id);
            $solution_files_q = $query->execute();*/
            //$solution_dependency_files_q = $injected_database->query("SELECT * FROM {lab_migration_solution_dependency} WHERE solution_id = %d", $solution_row->id);
            $query = \Drupal::database()->select('lab_migration_solution_dependency');
            $query->fields('lab_migration_solution_dependency');
            $query->condition('solution_id', $solution_row->id);
            $solution_dependency_files_q = $query->execute();
            while ($solution_files_row = $solution_files_q->fetchObject())
              {
                $zip->addFile($root_path . $solution_files_row->directory_name . '/' . $solution_files_row->filepath, $EXP_PATH . $CODE_PATH . str_replace(' ', '_', ($solution_files_row->filename)));
                //var_dump($zip->numFiles);
              }
            // die;
            /* dependency files */
            while ($solution_dependency_files_row = $solution_dependency_files_q->fetchObject())
              {
                //$dependency_file_data = ($injected_database->query("SELECT * FROM {lab_migration_dependency_files} WHERE id = %d LIMIT 1", $solution_dependency_files_row->dependency_id))->fetchObject();
                $query = \Drupal::database()->select('lab_migration_dependency_files');
                $query->fields('lab_migration_dependency_files');
                $query->condition('id', $solution_dependency_files_row->dependency_id);
                $query->range(0, 1);
                $dependency_file_data = $query->execute()->fetchObject();
                if ($dependency_file_data)
                    $zip->addFile($root_path . $dependency_file_data->filepath, $EXP_PATH . $CODE_PATH . 'DEPENDENCIES/' . str_replace(' ', '_', ($dependency_file_data->filename)));
              }
          }
      }
    $zip_file_count = $zip->numFiles;
    $zip->close();
    if ($zip_file_count > 0)
      {
        if ($user->uid)
          {
            /* download zip file */
            header('Content-Type: application/zip');
            header('Content-disposition: attachment; filename="' . str_replace(' ', '_', $lab_data->lab_title) . '.zip"');
            header('Content-Length: ' . filesize($zip_filename));
            ob_clean();
            //flush();
            readfile($zip_filename);
            unlink($zip_filename);
          }
        else
          {
            header('Content-Type: application/zip');
            header('Content-disposition: attachment; filename="' . str_replace(' ', '_', $lab_data->lab_title) . '.zip"');
            header('Content-Length: ' . filesize($zip_filename));
            header("Content-Transfer-Encoding: binary");
            header('Expires: 0');
            header('Pragma: no-cache');
            ob_end_flush();
            ob_clean();
            flush();
            readfile($zip_filename);
            unlink($zip_filename);
          }
      }
    else
      {
        \Drupal::messenger()->addError("There are no solutions in this Lab to download");
        RedirectResponse('lab-migration/lab-migration-run');
      }
  }
function lab_migration_download_syllabus_copy()
{
  $proposal_id = (int)arg(3);
  $root_path = lab_migration_path();
  $query = \Drupal::database()->select('lab_migration_proposal');
  $query->fields('lab_migration_proposal');
  $query->condition('id', $proposal_id);
  $query->range(0, 1);
  $result = $query->execute();
  $syllabus_copy_file_data = $result->fetchObject();
  $syllabus_copy_file_name = substr($syllabus_copy_file_data->syllabus_copy_file_path, strrpos($syllabus_copy_file_data->syllabus_copy_file_path, '/') + 1);
  error_reporting(0); //Errors may corrupt download
  ob_start(); //Insert this
  header('Content-Description: File Transfer');
  header('Content-Type: application/octet-stream');
  header('Content-disposition: attachment; filename="' . $syllabus_copy_file_name . '"');
  header('Content-Length: ' . filesize($root_path . $syllabus_copy_file_data->syllabus_copy_file_path));
  ob_clean();
  ob_end_flush();
  readfile($root_path . $syllabus_copy_file_data->syllabus_copy_file_path);
  exit;
}