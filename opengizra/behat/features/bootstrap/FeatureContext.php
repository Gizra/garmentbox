<?php

use Drupal\DrupalExtension\Context\DrupalContext;
use Behat\Behat\Context\Step\Given;
use Behat\Gherkin\Node\TableNode;

require 'vendor/autoload.php';

class FeatureContext extends DrupalContext {

  /**
   * @Given /^I am on a "([^"]*)" page with id "([^"]*)"$/
   */
  public function iAmOnAPageWithId($arg1, $arg2) {
    $path = 'node/' . $arg2;

    // Use Drupal Context 'I am at'.
    return new Given("I am at \"$path\"");
  }

  /**
   * @Given /^I should see the following <links>$/
   */
  public function iShouldSeeTheFollowingLinks(TableNode $table) {
    $page = $this->getSession()->getPage();
    $table = $table->getHash();

    foreach ($table as $key => $value) {
      $link = $table[$key]['links'];
      $result = $page->findLink($link);
      if(empty($result)) {
        throw new \Exception("The link '$link' was not found");
      }
    }
  }

  /**
   * @Then /^I should see a table titled "([^"]*)" with the following <contents>:$/
   */
  public function iShouldSeeATableTitledWithTheFollowingContents($title, TableNode $expected_table) {
    $page = $this->getSession()->getPage();
    // Find the container of the table with the correct pane title
    $element = $page->find('xpath', '//h2[.="' . $title .'"]/parent::div');
    if (!$element) {
      // If not found, search for a table with $title as its caption. Select
      // the parent of the table element.
      $element = $page->find('xpath', '//caption[.="' . $title .'"]/../..');
    }
    if (!$element) {
      throw new \Exception("No table titled '$title' was found.");
    }

    $table_element = $element->find('css', 'table');
    if (!$table_element) {
      throw new \Exception("No table was found inside the pane titled '$title'.");
    }

    self::compareTable($table_element, $expected_table);
  }

  /**
   * @Given /^the order "([^"]*)" should have these <inventory lines>$/
   */
  public function theOrderShouldHaveTheseInventoryLines($order_title, TableNode $expected_table) {
    $page = $this->getSession()->getPage();
    $element = $page->find('xpath', '//a[.="' . $order_title .'"]/../..');
    if (!$element) {
      throw new \Exception("The row holding order '$order_title' was not found.");
    }
    $inventory_wrapper_id = $element->getAttribute('ref');
    $table_element = $page->find('css', "#$inventory_wrapper_id");
    if (!$table_element) {
      throw new \Exception("The inventory lines table of order '$order_title' was not found.");
    }
    self::compareTable($table_element, $expected_table);
  }

  /**
   * @Given /^the BOM total should be "([^"]*)"$/
   */
  public function theBomTotalShouldBe($total) {
    if ($this->getSession()->getPage()->find('css', '.bom-total .amount')->getText() != $total) {
      throw new \Exception("The BOM has a different total price than '$total'.");
    }
  }

  /**
   * @Given /^the "([^"]*)" price should be "([^"]*)"$/
   */
  public function thePriceShouldBe($price_type, $price) {
    switch ($price_type) {
      case 'production':
        $selector = '.pane-production-price';
        break;

      case 'wholesale':
      case 'retail':
        $selector = ".field-name-field-{$price_type}-price";
        break;
    }
    if ($this->getSession()->getPage()->find('css', "$selector .field-item")->getText() != $price) {
      throw new \Exception("The production price is not '$price'.");
    }
  }


  /**
   * @Given /^the page status is shown as "([^"]*)"$/
   */
  public function thePageStatusIsShownAs($status) {
    if (!$this->getSession()->getPage()->find('xpath', '//div[contains(@class, "field-item") and .="' . $status . '"]')) {
      throw new Exception("Missing indication for status '$status'.");
    }
  }

  /**
   * Compare a present table with an expected table.
   *
   * @param $table_element
   *   A NodeElement containing a table.
   * @param $expected_table
   *   TableNode containing the expected table.
   */
  private static function compareTable($table_element, TableNode $expected_table) {
    $element_head = $table_element->find('css', 'thead');
    $expected_rows = $expected_table->getRows();
    $expected_head_row = array_shift($expected_rows);
    // Compare the table header.
    self::compareTableRow($element_head->findAll('css', 'th'), $expected_head_row);

    // Compare the rows.
    foreach ($table_element->findAll('css', 'tbody tr') as $i => $row) {
      if (empty($expected_rows[$i])) {
        break;
      }
      self::compareTableRow($row->findAll('css', 'td'), $expected_rows[$i]);
    }
  }

  /**
   * Compare a present table row cells with the expected row.
   *
   * @param $cells
   *   Array of NodeElement: Table row cells retrieved with findAll().
   * @param $expected_row
   *   One row from the TableNode object.
   */
  private static function compareTableRow($cells, $expected_row) {
    foreach ($cells as $i => $cell) {
      if (!array_key_exists($i, $expected_row)) {
        print_r($expected_row);
        throw new \Exception("Unexpected cell with text '{$cell->getText()}'.");
      }

      switch ($expected_row[$i]) {
        case '<ignore>':
          continue 2;

        case '<image>':
          // Make sure the cell contains an image tag.
          if (!$cell->find('css', 'img')) {
            throw new \Exception('Missing image');
          }
          break;

        default:
          $content = self::getText($cell->getHtml());
          if ($content != $expected_row[$i]) {
            throw new \Exception("Found '$content' instead of '{$expected_row[$i]}'.");
          }
      }
    }

    if (count($expected_row) > $i + 1) {
      throw new \Exception('Missing column.');
    }
  }

  /**
   * TODO: This method should be in a class extending BrowserKitDriver.
   *
   * Strip HTML but insert spaces between elements. Taken from the comments on:
   * http://php.net/manual/en/function.strip-tags.php
   *
   * @param $html
   *   Plain HTML.
   *
   * @return
   *   Stripped contents of the HTML.
   */
  private static function getText($html) {
     // Remove HTML tags.
    $html = preg_replace ('/<[^>]*>/', ' ', $html);

    // Remove control characters.
    $html = str_replace("\r", '', $html);
    $html = str_replace("\n", ' ', $html);
    $html = str_replace("\t", ' ', $html);

    // Remove multiple spaces.
    return trim(preg_replace('/ {2,}/', ' ', $html));
  }
}
