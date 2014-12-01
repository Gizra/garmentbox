<?php

use Drupal\DrupalExtension\Context\DrupalContext;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;

class FeatureContext extends DrupalContext implements SnippetAcceptingContext {

  /**
  * Initializes context.
  */
  public function __construct() {

  }

  /**
  * @When /^I visit the front page$/
  */
  public function iVisitTheFrontPage() {
    $steps = array();
    $steps[] = new Step\When('I am at "/"');
    return $steps;
  }

  /**
  * @When /^I am on edit page for the content "([^"]*)"$/
  */
  public function iAmOnEditPageForTheContent($title) {
    $query = new entityFieldQuery();
    $result = $query
    ->entityCondition('entity_type', 'node')
    ->propertyCondition('title', $title)
    ->propertyCondition('status', NODE_PUBLISHED)
    ->range(0, 1)
    ->execute();

    if (empty($result['node'])) {
      $params = array(
        '@title' => $title,
      );
      throw new Exception(format_string("Node @title not found.", $params));
    }

    $nid = key($result['node']);
    return array(
    new Step\When('I am on "node/' . $nid . '/edit"'),
    );
  }

  /**
  * @When /^I visit node "([^"]*)"$/
  */
  public function iVisitNode($title, $type) {
    $query = new entityFieldQuery();
    $result = $query
    ->entityCondition('entity_type', 'node')
    ->propertyCondition('title', $title)
    ->propertyCondition('status', NODE_PUBLISHED)
    ->range(0, 1)
    ->execute();

    if (empty($result['node'])) {
      $params = array('@title' => $title);
      throw new Exception(format_string("Node @title not found.", $params));
    }

    $nid = key($result['node']);
    return new Given("I go to \"node/$nid\"");
  }

  /**
  * @AfterStep
  *
  * Take a screen shot after failed steps for Selenium drivers (e.g.
  * PhantomJs).
  */
  public function takeScreenshotAfterFailedStep($event) {
    if ($event->getTestResult()->isPassed()) {
      // Not a failed step.
      return;
    }

    if ($this->getSession()->getDriver() instanceof \Behat\Mink\Driver\Selenium2Driver) {
      $screenshot = $this->getSession()->getDriver()->getScreenshot();
      file_put_contents('/tmp/behat-failed-step-screenshot.png', $screenshot);
    }
  }
}
