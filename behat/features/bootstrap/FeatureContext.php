<?php

use Drupal\DrupalExtension\Context\DrupalContext;

class FeatureContext extends DrupalContext {

  /**
  * Initializes context.
  *
  * Every scenario gets its own context object.
  *
  * @param array $parameters.
  *   Context parameters (set them up through behat.yml or behat.local.yml).
  */
  public function __construct(array $parameters) {
    if (!empty($parameters['drupal_users'])) {
      $this->drupal_users = $parameters['drupal_users'];
    }
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
  * @When /^I am on edit page for the node "([^"]*)"$/
  */
  public function iAmOnEditPageForTheNode($title) {
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
    if ($event->getResult() != 4) {
      // Not a failed step.
      return;
    }

    if ($this->getSession()->getDriver() instanceof \Behat\Mink\Driver\Selenium2Driver) {
      $screenshot = $this->getSession()->getDriver()->getScreenshot();
      file_put_contents('/tmp/behat-failed-step-screenshot.png', $screenshot);
    }
  }
}
