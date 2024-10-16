<?php
function lab_migration_completed_labs_proposal()
  {
    $output = "";
    //$query = "SELECT * FROM {lab_migration_proposal} WHERE approval_status = 3";
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('approval_status', 3);
    $query->orderBy('approval_date', DESC);
    $result = $query->execute();
    //$result = $injected_database->query($query);
    if ($result->rowCount() == 0)
      {
        $output .= "We are in the process of updating the lab migration data. ";
      }
    else
      {
        $preference_rows = array();
        $i = $result->rowCount();
        while ($row = $result->fetchObject())
          {
            $approval_date = date("Y", $row->approval_date);
            // @FIXME
// \Drupal\Core\Link expects a Url object, created from a route name or external URI.
// $preference_rows[] = array(
//                 $i,
//                 $row->university,
//                 l($row->lab_title, "lab-migration/lab-migration-run/" . $row->id),
//                 $approval_date
//             );

            $i--;
          }
        $preference_header = array(
            'No',
            'Institute',
            'Lab',
            'Year'
        );
        // @FIXME
// _theme has been renamed to __theme and should NEVER be called directly.
// Calling __theme directly can alter the expected output and potentially
// introduce security issues (see https://www.drupal.org/node/2195739). You
// should use renderable arrays instead.
// 
// 
// @see https://www.drupal.org/node/2195739
// $output .= theme('table', array(
//             'header' => $preference_header,
//             'rows' => $preference_rows
//         ));

      }
    return $output;
  }
function lab_migration_labs_progress_proposal()
  {
    $page_content = "";
    //$query = "SELECT * FROM {lab_migration_proposal} WHERE approval_status = 1 and solution_status = 2";
    $query = \Drupal::database()->select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('approval_status', 1);
    $query->condition('solution_status', 2);
    $result = $query->execute();
    if ($result->rowCount() == 0)
      {
        $page_content .= "We are in the process of updating the lab migration data. ";
      }
    else
      {
        //$result = $injected_database->query($query);
        $page_content .= "<ol reversed>";
        while ($row = $result->fetchObject())
          {
            $page_content .= "<li>";
            $page_content .= $row->university . " ({$row->lab_title})";
            $page_content .= "</li>";
          }
        $page_content .= "</ol>";
      }
    return $page_content;
  }
