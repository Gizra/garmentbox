Feature: Test tasks
  Test creation of task revisions through its comments.

  @api
  Scenario: Create a comment on a task while changing some task fields and
  verify that the changes are shown correctly.
    Given I am logged in as a user from "Imanimo"
      And I am on the default "task" page
     When I fill in "Subject" with "New title"
      And I fill in "Date" with "12/30/2012"
      And I select "Needs work" from "Status"
      And I fill in "Comment" with "Test"
      And I select "imanimo" from "Assignee"
      And I press "Save"
     Then I should see "Title: Prepare patterns » New title"
      And I should see "Status: Completed » Needs work"
      And I should see "Deadline: [None] » Sunday, December 30, 2012"
      And I should see "Assignee: [None] » imanimo"
