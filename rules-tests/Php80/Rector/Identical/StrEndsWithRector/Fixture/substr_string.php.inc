<?php

namespace Rector\Tests\Php80\Rector\Identical\StrEndsWithRector\Fixture;

class SubstrString
{
    public function run()
    {
        $isMatch = substr($haystack, -5) === 'value';

        $isMatch = 'value' === substr($haystack, -5);
    }
}

?>
-----
<?php

namespace Rector\Tests\Php80\Rector\Identical\StrEndsWithRector\Fixture;

class SubstrString
{
    public function run()
    {
        $isMatch = str_ends_with($haystack, 'value');

        $isMatch = str_ends_with($haystack, 'value');
    }
}

?>
