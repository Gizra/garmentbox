Feature: User login
  In order to be able to be recognized by the site
  As an anonymous user
  We need to be able to login to the site

  @api
  Scenario: Login to site, and check access to the homepage.
    Given I am an anonymous user
     When I am logged in as a user with the "authenticated user" role
     Then I should have access to the homepage
      But I should not have access to the login page
